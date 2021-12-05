#include "sem/types.hpp"

#include <functional>
#include <string>

#include "esl/boolean.hpp"
#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"

#include "config.hpp"
#include "sem/interface.hpp"
#include "sem/misc.hpp"
#include "sem/numeric_types.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace esl {

    using cynth::sem::CompleteType;
    using cynth::sem::IncompleteType;

    template <>
    void component_deleter<CompleteType>::operator () (CompleteType * ptr) const {
        delete ptr;
    }

    template <>
    CompleteType * component_allocator<CompleteType>::operator () (CompleteType const & other) const {
        return new CompleteType{other};
    }

    template <>
    CompleteType * component_allocator<CompleteType>::operator () (CompleteType && other) const {
        return new CompleteType{std::move(other)};
    }

    template <>
    void component_deleter<IncompleteType>::operator () (IncompleteType * ptr) const {
        delete ptr;
    }

    template <>
    IncompleteType * component_allocator<IncompleteType>::operator () (IncompleteType const & other) const {
        return new IncompleteType{other};
    }

    template <>
    IncompleteType * component_allocator<IncompleteType>::operator () (IncompleteType && other) const {
        return new IncompleteType{std::move(other)};
    }

}

#if 0
namespace cynth::sem {

    //// Bool ////

    DisplayResult type::Bool::display () const {
        return "Bool";
    }

    /** `cth_t_Bool` */
    TypeTranslationResult type::Bool::translateType () const {
        return std::string{} + prefix::global + "_" + prefix::type + "_Bool";
    }

    CommonTypeResult type::Bool::commonType (type::Bool const &) const {
        return {type::Bool{}};
    }

    CommonTypeResult type::Bool::commonType (type::Int const &) const {
        return {type::Int{}};
    }

    CommonTypeResult type::Bool::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    CommonTypeResult type::Bool::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Bool::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    bool type::Bool::sameType (type::Bool const &) const {
        return true;
    }

    //// Int ////

    DisplayResult type::Int::display () const {
        return "Int";
    }

    /** `cth_t_Int` */
    TypeTranslationResult type::Int::translateType () const {
        return std::string{} + prefix::global + "_" + prefix::type + "_Int";
    }

    CommonTypeResult type::Int::commonType (type::Int const &) const {
        return {type::Int{}};
    }

    CommonTypeResult type::Int::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    CommonTypeResult type::Int::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Int::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    bool type::Int::sameType (type::Int const &) const {
        return true;
    }

    //// Float ////

    DisplayResult type::Float::display () const {
        return "Float";
    }

    /** `cth_t_Float` */
    TypeTranslationResult type::Float::translateType () const {
        return std::string{} + prefix::global + "_" + prefix::type + "_Float";
    }

    CommonTypeResult type::Float::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    CommonTypeResult type::Float::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Float::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    bool type::Float::sameType (type::Float const &) const {
        return true;
    }

    //// String ////

    DisplayResult type::String::display () const {
        return "String";
    }

    /** `cth_t_String` */
    TypeTranslationResult type::String::translateType () const {
        return std::string{} + prefix::global + "_" + prefix::type + "_String";
    }

    CommonTypeResult type::String::commonType (type::String const &) const {
        return {type::String{}};
    }

    bool type::String::sameType (type::String const &) const {
        return true;
    }

    //// In ////

    DisplayResult type::In::display () const {
        return "T in"; // TODO
    }

    /** `T` */
    TypeTranslationResult type::In::translateType () const {
        return esl::lift<esl::target::component, esl::target::category>(sem::translateType)(type);
    }

    TypeDecayResult type::In::decayType () const {
        return *type;
    }

    bool type::In::sameType (type::In const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
    }

    TypeCompletionResult type::IncompleteIn::completeType (Context & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::In{{
            .type = *result
        }}};
    }

    //// Out ////

    DisplayResult type::Out::display () const {
        return "T out"; // TODO
    }

    /** `T` */
    TypeTranslationResult type::Out::translateType () const {
        return esl::lift<esl::target::component, esl::target::category>(sem::translateType)(type);
    }

    TypeDecayResult type::Out::decayType () const {
        return *type;
    }

    bool type::Out::sameType (type::Out const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
    }

    TypeCompletionResult type::IncompleteOut::completeType (Context & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::Out{{
            .type = *result
        }}};
    }

    //// Const ////

    DisplayResult type::Const::display () const {
        return "T const"; // TODO
    }

    /** `T const` */
    TypeTranslationResult type::Const::translateType () const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::translateType)(type);
        if (!result)
            return result.error();
        return *result + " const";
    }

    TypeDecayResult type::Const::decayType () const {
        return *type;
    }

    CommonTypeResult type::Const::commonType (type::Const const & other) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::commonType)(type, other.type);
        if (!result)
            return result.error();
        return {type::Const{{
            .type = *result
        }}};
    }

    bool type::Const::sameType (type::Const const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
    }

    TypeCompletionResult type::IncompleteConst::completeType (Context & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::Const{{
            .type = *result
        }}};
    }

    //// Array ////

    esl::result<type::Array> type::Array::make (esl::component_vector<CompleteType> && type, sem::Integral size) {
        if (size <= 0)
            return esl::result_error{"Array must have a positive size."};
        auto elemTypeCheck =
            esl::unite_results(esl::lift<esl::target::vector, esl::target::component>(arrayElemTypeCheck)(type));
        if (!elemTypeCheck)
            return elemTypeCheck.error();
        return type::Array{{
            .type = std::move(type),
            .size = size
        }};
    }

    DisplayResult type::Array::display () const {
        return "T [n]"; // TODO
    }

    /** `T *` */
    TypeTranslationResult type::Array::translateType () const {
        auto result =
            esl::lift<esl::target::result, esl::target::category>(sem::translateType)(esl::single(type));
        if (!result)
            return result.error();
        return *result + " *";
    }

    type::Array::commonType (type::Array const & other) const {
        auto results = (esl::lift<esl::target::component, esl::target::category>(
            [] <typename T, typename U> (T const & a, U const & b) -> std::optional<CompleteType> {
            //requires (std::sameType_as<T, U> || !std::sameType_as<T, type::Const> && std::sameType_as<U, type::Const>)
                if (sameType(a, b))
                    return {a};
                return {};
            },
            [] <typename T> (type::Const const & a, T const & b) -> std::optional<CompleteType>
            requires (!std::same_as<T, type::Const>) {
                if (sameType(a, b))
                    return {a};
                if (sameType(a, type::Const{{b}}))
                    return {type::Const{{a}}};
                return {};
            },
            [] <typename T> (T const & a, type::Const const & b) -> std::optional<CompleteType>
            requires (!std::same_as<T, type::Const>) {
                if (sameType(a, b))
                    return {a};
                if (sameType(type::Const{{a}}, b))
                    return {type::Const{{a}}};
                return {};
            }
        )(type, other.type));
        if (!results)
            return results.error();
        auto result = esl::unite_optionals(*results);
        if (!result)
            return esl::result_error{"No common type for two arrays because of mismatched elements type."};
        auto arrayResult = type::Array::make(
            make_component_vector(*result),
            std::min(size, other.size)
        );
        if (!arrayResult)
            return arrayResult.error();
        return {*arrayResult};
    }

    bool type::Array::sameType (type::Array const & other) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
        return result && size == other.size && esl::all(*result);
    }

    TypeCompletionResult type::IncompleteArray::completeType (Context & ctx) const {
        auto typeResult = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!typeResult)
            return typeResult.error();

        auto sizeResult = lift2<component, target::category>(
            [] (value::unknown const &) -> result<int> {
                return esl::result_error{"Unknown array size."};
            },
            [&ctx] <interface::value Value> (Value const & value) -> result<int> {
                return get<Integral>(convert(ctx)(type::Int{})(value));
            }
        )(size);
        if (!sizeResult)
            return sizeResult.error();

        auto arrayResult = type::Array::make(
            make_component_vector(*typeResult),
            *sizeResult
        );
        if (!arrayResult)
            return arrayResult.error();
        return {*arrayResult};
    }
    template TypeCompletionResult type::array_type<false>::complete (Context &) const;

    //// Buffer ////

    result<type::Buffer> type::Buffer::make (integral size) {
        if (size <= 0)
            return esl::result_error{"Buffer must have a positive size."};
        return type::Buffer {
            .size = size
        };
    }

    /** `float *` */
    template <>
    TypeTranslationResult type::Buffer::translateType () const {
        // This assumes that type::Float always returns a non-error value.
        return *type::Float{}.translateType() + " *";
    }

    template <>
    DisplayResult type::Buffer::display () const {
        return "buffer [n]"; // TODO
    }

    template <bool Complete>
    CommonTypeResult type::buffer_type<Complete>::commonType (type::Buffer const & other) const requires Complete {
        if (size != other.size)
            return esl::result_error{"No common type for two buffers because of different sizes."};
        return {*this};
    }
    template CommonTypeResult type::buffer_type<true>::commonType (type::Buffer const & other) const;

    template <bool Complete>
    bool type::buffer_type<Complete>::sameType (type::Buffer const & other) const requires Complete {
        return size == other.size;
    }
    template bool type::buffer_type<true>::sameType (type::Buffer const & other) const;

    template <bool Complete>
    TypeCompletionResult type::buffer_type<Complete>::complete (Context & ctx) const requires (!Complete) {
        auto sizeResult = lift2<component, target::category>(
            [] (value::unknown const &) -> result<integral> {
                return esl::result_error{"Unknown array size."};
            },
            [&ctx] <interface::value Value> (Value const & value) -> result<integral> {
                return get<integral>(convert(ctx)(type::Int{})(value));
            }
        )(size);
        if (!sizeResult)
            return sizeResult.error();

        auto bufferResult = type::Buffer::make(*sizeResult);
        if (!bufferResult)
            return bufferResult.error();

        return {*bufferResult};
    }
    template TypeCompletionResult type::buffer_type<false>::complete (Context &) const;

    //// Function ////

    template <>
    DisplayResult type::Function::display () const {
        return "Output (Input)"; // TODO
    }

    template <>
    TypeTranslationResult type::Function::translateType () const {
        return esl::result_error{"Function types are not directly translatable."};
    }

    template <bool Complete>
    CommonTypeResult type::function_type<Complete>::commonType (type::Function const & other) const requires Complete {
        auto outResult = sameType(out, other.out);
        if (!outResult)
            return outResult.error();
        if (!esl::all(*outResult))
            return esl::result_error{"No common type for two functions because of diferent output types."};
        auto inResult = sameType(in, other.in);
        if (!inResult)
            return inResult.error();
        if (!esl::all(*inResult))
            return esl::result_error{"No common type for two functions because of diferent input types."};
        return {*this};
    }
    template CommonTypeResult type::function_type<true>::commonType (type::Function const & other) const;

    template <bool Complete>
    bool type::function_type<Complete>::sameType (type::Function const & other) const requires Complete {
        auto outResult = sameType(out, other.out);
        auto inResult  = sameType(in,  other.in);
        return
            outResult && esl::all(*outResult) &&
            inResult  && esl::all(*inResult);
    }
    template bool type::function_type<true>::sameType (type::Function const & other) const;

    template <bool Complete>
    TypeCompletionResult type::function_type<Complete>::complete (Context & ctx) const requires (!Complete) {
        auto outResult = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(out);
        if (!outResult)
            return outResult.error();
        auto inResult = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(in);
        if (!inResult)
            return inResult.error();
        return {type::Function{{
            .out = *outResult,
            .in  = *inResult,
        }}};
    }
    template TypeCompletionResult type::function_type<false>::complete (Context &) const;

}
#endif
