#include "sem/values.hpp"

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/view.hpp"

#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/values.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"
#include "syn/nodes/common/array_nodes.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace esl {

    using cynth::sem::CompleteValue;
    using cynth::sem::IncompleteValue;

    // Note: Some of these specializations are needed for the implementations below to work properly.
    // TODO: Maybe I should move it elsewhere. These specializations are only needed
    // for code that doesn't know about complete definitions of these types.
    // However, code in any of the implementation files can include the full definitions,
    // and so the default specializations can be used instead.

    template <>
    void component_deleter<CompleteValue>::operator () (CompleteValue * ptr) const {
        delete ptr;
    }

    template <>
    CompleteValue * component_allocator<CompleteValue>::operator () (CompleteValue const & other) const {
        return new CompleteValue{other};
    }

    template <>
    CompleteValue * component_allocator<CompleteValue>::operator () (CompleteValue && other) const {
        return new CompleteValue{std::move(other)};
    }

    template <>
    void component_deleter<IncompleteValue>::operator () (IncompleteValue * ptr) const {
        delete ptr;
    }

    template <>
    IncompleteValue * component_allocator<IncompleteValue>::operator () (IncompleteValue const & other) const {
        return new IncompleteValue{other};
    }

    template <>
    IncompleteValue * component_allocator<IncompleteValue>::operator () (IncompleteValue && other) const {
        return new IncompleteValue{std::move(other)};
    }

}

namespace cynth::sem {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::GetResult;
    using interface::ValueTranslationResult;

    //// Bool ////

    DisplayResult value::Bool::display () const {
        return "bool(" + std::string{value ? "true" : "false"} + ")";
    }

    GetResult<bool> value::Bool::get () const {
        return value;
    }

    ValueTranslationResult value::Bool::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::boolLiteral(value)};
    }

    //// Int ////

    DisplayResult value::Int::display () const {
        return "int(" + std::to_string(value) + ")";
    }

    GetResult<Integral> value::Int::get () const {
        return value;
    }

    ValueTranslationResult value::Int::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::intLiteral(value)};
    }

    //// Float ////

    DisplayResult value::Float::display () const {
        return "float(" + std::to_string(value) + ")";
    }

    GetResult<Floating> value::Float::get () const {
        return value;
    }

    ValueTranslationResult value::Float::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::floatLiteral(value)};
    }

    //// String ////

    DisplayResult value::String::display () const {
        return "string(" + value + ")";
    }

    ValueTranslationResult value::String::translateValue (context::Main &) const {
        return esl::result_error{"Strings are not implemented yet."};
    }

    //// In ////

    DisplayResult value::In::display () const {
        return "in(" + allocation + ")";
    }

    ValueTranslationResult value::In::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::addressof(allocation)}; // TODO: Cast to a const pointer?
    }

    //// Out ////

    DisplayResult value::Out::display () const {
        return "out(" + allocation + ")";
    }

    ValueTranslationResult value::Out::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::addressof(allocation)}; // TODO: Cast to a const pointer?
    }

    //// Array ////

    esl::view<ArrayAllocation::Vector::iterator> ArrayAllocation::trimmedValue (Integral size) {
        return esl::view{value.begin(), value.begin() + size};
    }

    std::string ArrayAllocation::allocate (context::Main & ctx) {
        if (variable)
            return *variable;

        auto result = [&] (auto translType, auto translElems) -> std::string {
            auto allocName = syn::array_nodes::arrayAllocation(ctx, std::move(translType), value.size());
            syn::array_nodes::individualArrayInitialization(ctx, allocName, translElems);
            variable = allocName;
            return *variable;

        } || target::result{} <<= args(
            interface::translateTypeSpecifier || target::category{} <<= type(),
            interface::expression || target::nested<target::result, target::tiny_vector>{} <<=
                esl::unite_results <<=
                interface::translateResolvedValue(ctx) || target::sized_range_tiny_result{} <<= value
        );

        // An esl::result_error would indicate an implementation error here.
        return *result;
    }

    ArithmeticSequence::ArithmeticSequence (Integral const & from, Integral const & to, Integral const & by):
        definition{
            CompleteValue{value::Int{from}},
            CompleteValue{value::Int{to}},
            CompleteValue{value::Int{by}}
        } {}

    std::optional<ArithmeticSequence> ArrayAllocation::sequentialize () {
        if (sequence)
            return *sequence;
        return [&] (sem::type::Int) -> std::optional<ArithmeticSequence> {
            Integral from;
            Integral count = 0;
            std::optional<Integral> step;
            std::optional<Integral> last;
            for (auto const & elem: value) {
                // Note: This assumes correct types.
                Integral val = elem.get<sem::value::Int>()->get();
                if (last) {
                    if (!step)
                        step = val - *last;
                    else if (step != val - *last)
                        return std::nullopt;
                } else {
                    last = val;
                    from = val;
                }
                ++count;
            }
            if (!step)
                return std::nullopt;
            sequence = ArithmeticSequence{from, from + count * *step, *step};
            return sequence;

        } | [] (auto) -> std::optional<ArithmeticSequence> {
            return std::nullopt;

        } || target::category{} <<= type();
    }

    CompleteType ArrayAllocation::type () const {
        return sequence ? sequence->type() : interface::valueType || target::category{} <<= value.front();
    }

    void ArrayAllocation::relax () {
        constant = false;
    }

    DisplayResult value::Array::display () const {
        return "array<" + valueType.display() + ">(...)";
    }

    ValueTranslationResult value::Array::translateValue (context::Main & ctx) const {
        return [&] (ArrayAllocation * alloc) -> ValueTranslationResult {
            auto val = alloc->allocate(ctx);
            return TypedExpression{*valueType.type, c::addressof(val)}; // TODO: Cast to a const pointer?

        } | [&] (std::string const & alloc) -> ValueTranslationResult {
            return TypedExpression{*valueType.type, c::addressof(alloc)}; // TODO: Cast to a const pointer?

        } || target::variant{} <<= allocation;
    }

    //// Buffer ////

    DisplayResult value::Buffer::display () const {
        return "buffer(...)";
    }

    //// Function ////

    DisplayResult value::Function::display () const {
        return "function(...)";
    }

    ValueTranslationResult value::Buffer::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::addressof(allocation)}; // TODO: Cast to a const pointer?
    }

}
