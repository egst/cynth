#include "syn/nodes/range_declarations.hpp"

#include <utility>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"

#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/declarations.hpp"

namespace esl {

    using cynth::syn::node::RangeDecl;
    using cynth::syn::node::TupleRangeDecl;

    template <>
    void component_deleter<RangeDecl>::operator () (RangeDecl * ptr) const {
        delete ptr;
    }

    template <>
    RangeDecl * component_allocator<RangeDecl>::operator () (RangeDecl const & other) const {
        return new RangeDecl{other};
    }

    template <>
    RangeDecl * component_allocator<RangeDecl>::operator () (RangeDecl && other) const {
        return new RangeDecl{std::move(other)};
    }

    template <>
    void component_deleter<TupleRangeDecl>::operator () (TupleRangeDecl * ptr) const {
        delete ptr;
    }

    template <>
    TupleRangeDecl * component_allocator<TupleRangeDecl>::operator () (
        TupleRangeDecl const & other
    ) const {
        return new TupleRangeDecl{other};
    }

    template <>
    TupleRangeDecl * component_allocator<TupleRangeDecl>::operator () (
        TupleRangeDecl && other
    ) const {
        return new TupleRangeDecl{std::move(other)};
    }

}

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::RangeDeclarationResolutionResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteRangeDeclaration;

    //// RangeDecl ////

    DisplayResult node::RangeDecl::display () const {
        return
            (interface::display || target::category{} <<= *declaration) + " in " +
            (interface::display || target::category{} <<= *range);
    }

    RangeDeclarationResolutionResult node::RangeDecl::resolveRangeDeclaration (context::Main & ctx) const {
        return [&] (auto && decls, auto && range) {
            return esl::init<esl::tiny_vector>(CompleteRangeDeclaration{
                esl::make_component_vector(std::move(decls)),
                std::move(range)
            });

        } || target::result{} <<= args(
            interface::resolveDeclaration(ctx) || target::category{} <<= *declaration,
            esl::single || target::result{} <<=
                interface::processExpression(ctx) || target::category{} <<= *range
        );
    }

    NameExtractionResult node::RangeDecl::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *range,
            interface::extractNames(ctx) || target::category{} <<= *declaration
        );
    }

    TypeNameExtractionResult node::RangeDecl::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *declaration,
            interface::extractTypeNames(ctx) || target::category{} <<= *range
        );
    }

    //// TupleRangeDecl ////

    DisplayResult node::TupleRangeDecl::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return "(" + esl::join(", ", interface::display || Target{} <<= declarations) + ")";
    }

    RangeDeclarationResolutionResult node::TupleRangeDecl::resolveRangeDeclaration (context::Main & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::resolveRangeDeclaration(ctx) || target::nested<target::component_vector, target::category>{} <<=
            declarations;
    }

    NameExtractionResult node::TupleRangeDecl::extractNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            declarations;
    }

    TypeNameExtractionResult node::TupleRangeDecl::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractTypeNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            declarations;
    }

}
