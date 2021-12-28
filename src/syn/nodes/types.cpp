#include "syn/nodes/types.hpp"

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::TypeResolutionResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::IO;
    using sem::Integral;
    using sem::TypedExpression;

    //// ArrayType ////

    DisplayResult node::ArrayType::display () const {
        using SizeTarget = target::nested<target::optional_component, target::category>;
        return
            (interface::display || target::category{} <<= *type) + " [" +
            (interface::display || SizeTarget{} <<= size).value_or("$") + "]";
    }

    TypeResolutionResult node::ArrayType::resolveType (context::Main & ctx) const {
        using SizeTarget = target::nested<target::optional_component, target::category>;
        auto sizeResult =
            [&] (interface::has::processExpression auto && expr) {
                return [&] (CompleteValue && value) -> esl::result<Integral> {
                    auto valueResult = std::move(value).get<sem::value::Int>();
                    if (!valueResult) return valueResult.error();
                    return interface::get<Integral>(*std::move(valueResult));

                } | [&] (TypedExpression &&) -> esl::result<Integral> {
                    return esl::result_error{"Array size must be a compconst value."};

                } || target::nested<target::result, target::category>{} <<= esl::single || target::result{} <<=
                    interface::processExpression(ctx)(std::move(expr));

            } | [] (interface::has::resolveDeclaration auto &&) -> esl::result<Integral> {
                return esl::result_error{"Capturing array size deduction is not supported yet."};

            } || SizeTarget{} <<= size;
        if (!sizeResult)
            return esl::result_error{"Array size deduction is not supported yet."};

        return [&] (auto && type, auto && size) {
            return esl::init<esl::tiny_vector>(CompleteType{sem::type::Array{std::move(type), std::move(size)}});

        } || target::result{} <<= args(
            esl::single || target::result{} <<= interface::resolveType(ctx) || target::category{} <<= *type,
            *std::move(sizeResult)
        );
    }

    //// Auto ////

    DisplayResult node::Auto::display () const {
        return "$";
    }

    TypeResolutionResult node::Auto::resolveType (context::Main &) const {
        return esl::result_error{"The auto type is not supported yet."};
    }

    //// BufferType ////

    DisplayResult node::BufferType::display () const {
        return "buffer [" + (interface::display || target::category{} <<= *size) + "]";
    }

    TypeResolutionResult node::BufferType::resolveType (context::Main & ctx) const {
        auto sizeResult =
            [&] (CompleteValue && value) -> esl::result<Integral> {
                auto valueResult = std::move(value).get<sem::value::Int>();
                if (!valueResult) return valueResult.error();
                return interface::get<Integral>(*std::move(valueResult));

            } | [&] (TypedExpression &&) -> esl::result<Integral> {
                return esl::result_error{"Array size must be a compconst value."};

            } || target::nested<target::result, target::category>{} <<= esl::single || target::result{} <<=
                interface::processExpression(ctx) || target::category{} <<= *size;

        return [&] (auto && size) {
            return esl::init<esl::tiny_vector>(CompleteType{sem::type::Buffer{std::move(size)}});

        } || target::result{} <<= std::move(sizeResult);
    }

    //// ConstType ////

    DisplayResult node::ConstType::display () const {
        return (interface::display || target::category{} <<= *type) + " const";
    }

    TypeResolutionResult node::ConstType::resolveType (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [] (sem::type::In && type) -> esl::result<CompleteType> {
                // Note: Input types are implicitly const.
                return {std::move(type)};

            } | [] (sem::type::Out && type) -> esl::result<CompleteType> {
                // Note: Output types are implicitly const.
                return {std::move(type)};

            } | [] (sem::type::Buffer && type) -> esl::result<CompleteType> {
                // Note: Buffers are implicitly const.
                return {std::move(type)};

            } | [] (sem::type::Function && type) -> esl::result<CompleteType> {
                // Note: Function types are implicitly const.
                return {std::move(type)};

            } | [] (sem::type::Array && type) -> esl::result<CompleteType> {
                type.constref = true;
                return {std::move(type)};

            } | [] (interface::simpleType auto && type) -> esl::result<CompleteType> {
                type.constant = true;
                return {std::move(type)};

            } | [] (sem::type::String && type) -> esl::result<CompleteType> {
                return esl::result_error{"Strings are not supoorted yet."};

            } || target::nested<target::result, target::tiny_vector, target::category>{} <<=
                interface::resolveType(ctx) || target::category{} <<= *type;
    }

    //// FunctionType ////

    DisplayResult node::FunctionType::display () const {
        return
            (interface::display || target::category{} <<= *output) + " " +
            esl::parenthesized(interface::display || target::category{} <<= *input);
    }

    TypeResolutionResult node::FunctionType::resolveType (context::Main & ctx) const {
        return [&] (auto && out, auto && in) -> TypeResolutionResult {
            return esl::init<esl::tiny_vector>(CompleteType{sem::type::Function{
                .in  = esl::make_component_vector(std::move(in)),
                .out = esl::make_component_vector(std::move(out))
            }});
        } || target::result{} <<= args(
            interface::resolveType(ctx) || target::category{} <<= *output,
            interface::resolveType(ctx) || target::category{} <<= *input
        );
    }

    //// InType ////

    DisplayResult node::InType::display () const {
        return (interface::display || target::category{} <<= *type) + " in";
    }

    TypeResolutionResult node::InType::resolveType (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [] (sem::type::In && type) -> esl::result<CompleteType> {
                return {std::move(type)};

            } | [] (sem::type::Out && type) -> esl::result<CompleteType> {
                return esl::result_error{"Input type cannot contain a nested output type."};

            } | [] (sem::type::Buffer && type) -> esl::result<CompleteType> {
                type.io = IO::input;
                return {std::move(type)};

            } | [] (sem::type::Function && type) -> esl::result<CompleteType> {
                return esl::result_error{"Function cannot an input type."};

            } | [] (sem::type::Array && type) -> esl::result<CompleteType> {
                return esl::result_error{"Array cannot an input type."};

            } | [] (interface::simpleType auto && type) -> esl::result<CompleteType> {
                return {sem::type::In{CompleteType{std::move(type)}}};

            } | [] (sem::type::String && type) -> esl::result<CompleteType> {
                return esl::result_error{"Strings are not supoorted yet."};

            } || target::nested<target::result, target::tiny_vector, target::category>{} <<=
                interface::resolveType(ctx) || target::category{} <<= *type;
    }

    //// OutType ////

    DisplayResult node::OutType::display () const {
        return (interface::display || target::category{} <<= *type) + " out";
    }

    TypeResolutionResult node::OutType::resolveType (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [] (sem::type::In && type) -> esl::result<CompleteType> {
                return esl::result_error{"Output type cannot contain a nested input type."};

            } | [] (sem::type::Out && type) -> esl::result<CompleteType> {
                return {std::move(type)};

            } | [] (sem::type::Buffer && type) -> esl::result<CompleteType> {
                type.io = IO::output;
                return {std::move(type)};

            } | [] (sem::type::Function && type) -> esl::result<CompleteType> {
                return esl::result_error{"Function cannot an output type."};

            } | [] (sem::type::Array && type) -> esl::result<CompleteType> {
                return esl::result_error{"Array cannot an output type."};

            } | [] (interface::simpleType auto && type) -> esl::result<CompleteType> {
                return {sem::type::Out{CompleteType{std::move(type)}}};

            } | [] (sem::type::String && type) -> esl::result<CompleteType> {
                return esl::result_error{"Strings are not supoorted yet."};

            } || target::nested<target::result, target::tiny_vector, target::category>{} <<=
                interface::resolveType(ctx) || target::category{} <<= *type;
    }

    //// TupleType ////

    DisplayResult node::TupleType::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return "(" + esl::join(", ", interface::display || Target{} <<= types) + ")";
    }

    TypeResolutionResult node::TupleType::resolveType (context::Main & ctx) const {
        TypeResolutionResult::value_type result;
        [&] (auto && types) {
            for (auto && tuple: types) for (auto && type: tuple) {
                result.push_back(std::move(type));
            }

        } || target::result{} <<= esl::unite_results <<=
            interface::resolveType(ctx) || target::nested<target::component_vector, target::category>{} <<=
            types;
        return result;
    }

    //// TypeDecl ////

    DisplayResult node::TypeDecl::display () const {
        return "type " + interface::display(name);
    }

    TypeResolutionResult node::TypeDecl::resolveType (context::Main &) const {
        return esl::result_error{"Capturing type deduction is not supported yet."};
    }

    //// TypeName ////

    DisplayResult node::TypeName::display () const {
        return *name;
    }

    TypeResolutionResult node::TypeName::resolveType (context::Main & ctx) const {
        auto value = ctx.lookup.findType(*name);
        if (!value)
            return esl::result_error{"Type name not found"};
        return {*value};
    }

}

namespace esl {

    using cynth::syn::node::ArrayType;
    using cynth::syn::node::Auto;
    using cynth::syn::node::BufferType;
    using cynth::syn::node::ConstType;
    using cynth::syn::node::FunctionType;
    using cynth::syn::node::InType;
    using cynth::syn::node::OutType;
    using cynth::syn::node::TupleType;
    using cynth::syn::node::TypeDecl;
    using cynth::syn::node::TypeName;

    template <>
    void component_deleter<ArrayType>::operator () (ArrayType * ptr) const {
        delete ptr;
    }

    template <>
    ArrayType * component_allocator<ArrayType>::operator () (ArrayType const & other) const {
        return new ArrayType{other};
    }

    template <>
    ArrayType * component_allocator<ArrayType>::operator () (ArrayType && other) const {
        return new ArrayType{std::move(other)};
    }

    template <>
    void component_deleter<Auto>::operator () (Auto * ptr) const {
        delete ptr;
    }

    template <>
    Auto * component_allocator<Auto>::operator () (Auto const & other) const {
        return new Auto{other};
    }

    template <>
    Auto * component_allocator<Auto>::operator () (Auto && other) const {
        return new Auto{std::move(other)};
    }

    template <>
    void component_deleter<BufferType>::operator () (BufferType * ptr) const {
        delete ptr;
    }

    template <>
    BufferType * component_allocator<BufferType>::operator () (BufferType const & other) const {
        return new BufferType{other};
    }

    template <>
    BufferType * component_allocator<BufferType>::operator () (BufferType && other) const {
        return new BufferType{std::move(other)};
    }

    template <>
    void component_deleter<ConstType>::operator () (ConstType * ptr) const {
        delete ptr;
    }

    template <>
    ConstType * component_allocator<ConstType>::operator () (ConstType const & other) const {
        return new ConstType{other};
    }

    template <>
    ConstType * component_allocator<ConstType>::operator () (ConstType && other) const {
        return new ConstType{std::move(other)};
    }

    template <>
    void component_deleter<FunctionType>::operator () (FunctionType * ptr) const {
        delete ptr;
    }

    template <>
    FunctionType * component_allocator<FunctionType>::operator () (FunctionType const & other) const {
        return new FunctionType{other};
    }

    template <>
    FunctionType * component_allocator<FunctionType>::operator () (FunctionType && other) const {
        return new FunctionType{std::move(other)};
    }

    template <>
    void component_deleter<InType>::operator () (InType * ptr) const {
        delete ptr;
    }

    template <>
    InType * component_allocator<InType>::operator () (InType const & other) const {
        return new InType{other};
    }

    template <>
    InType * component_allocator<InType>::operator () (InType && other) const {
        return new InType{std::move(other)};
    }

    template <>
    void component_deleter<OutType>::operator () (OutType * ptr) const {
        delete ptr;
    }

    template <>
    OutType * component_allocator<OutType>::operator () (OutType const & other) const {
        return new OutType{other};
    }

    template <>
    OutType * component_allocator<OutType>::operator () (OutType && other) const {
        return new OutType{std::move(other)};
    }

    template <>
    void component_deleter<TupleType>::operator () (TupleType * ptr) const {
        delete ptr;
    }

    template <>
    TupleType * component_allocator<TupleType>::operator () (TupleType const & other) const {
        return new TupleType{other};
    }

    template <>
    TupleType * component_allocator<TupleType>::operator () (TupleType && other) const {
        return new TupleType{std::move(other)};
    }

    template <>
    void component_deleter<TypeDecl>::operator () (TypeDecl * ptr) const {
        delete ptr;
    }

    template <>
    TypeDecl * component_allocator<TypeDecl>::operator () (TypeDecl const & other) const {
        return new TypeDecl{other};
    }

    template <>
    TypeDecl * component_allocator<TypeDecl>::operator () (TypeDecl && other) const {
        return new TypeDecl{std::move(other)};
    }

    template <>
    void component_deleter<TypeName>::operator () (TypeName * ptr) const {
        delete ptr;
    }

    template <>
    TypeName * component_allocator<TypeName>::operator () (TypeName const & other) const {
        return new TypeName{other};
    }

    template <>
    TypeName * component_allocator<TypeName>::operator () (TypeName && other) const {
        return new TypeName{std::move(other)};
    }

}
