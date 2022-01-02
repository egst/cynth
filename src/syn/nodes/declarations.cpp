#include "syn/nodes/declarations.hpp"

#include <utility>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "syn/nodes/common/decl_nodes.hpp"

// TMP
#include "debug.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DeclarationResolutionResult;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteDeclaration;
    using sem::NoReturn;

    namespace {

        StatementProcessingResult processStatementImpl (context::Main & ctx, interface::node auto const & decl) {
            return [&] (auto && decls) -> StatementProcessingResult {
                auto result = decl_nodes::declare(ctx, decls);
                if (!result)
                    return result.error();

                return {NoReturn{}};

            } || target::result{} <<= interface::resolveDeclaration(ctx)(decl);
        }

    }

    //// Declaration ////

    DisplayResult node::Declaration::display () const {
        return (interface::display || target::category{} <<= *type) + " " + interface::display(name);
    }

    DeclarationResolutionResult node::Declaration::resolveDeclaration (context::Main & ctx) const {
        return [&] (auto && type) {
            return esl::init<esl::tiny_vector>(CompleteDeclaration{
                esl::make_component_vector(std::move(type)),
                *name.name
            });

        } || target::result {} <<= interface::resolveType(ctx) || target::category{} <<= *type;
    }

    StatementProcessingResult node::Declaration::processStatement (context::Main & ctx) const {
        return processStatementImpl(ctx, *this);
    }

    NameExtractionResult node::Declaration::extractNames (context::Lookup & ctx) const {
        auto names = interface::extractNames(ctx) || target::category{} <<= *type;
        auto result = ctx.insertValue(*name.name, {});
        if (!result) return result.error();
        return names;
    }

    TypeNameExtractionResult node::Declaration::extractTypeNames (context::Lookup & ctx) const {
        return interface::extractTypeNames(ctx) || target::category{} <<= *type;
    }

    //// TupleDecl ////

    DisplayResult node::TupleDecl::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return "(" + esl::join(", ", interface::display || Target{} <<= declarations) + ")";
    }

    DeclarationResolutionResult node::TupleDecl::resolveDeclaration (context::Main & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::resolveDeclaration(ctx) || target::nested<target::component_vector, target::category>{} <<=
            declarations;
    }

    StatementProcessingResult node::TupleDecl::processStatement (context::Main & ctx) const {
        return processStatementImpl(ctx, *this);
    }

    NameExtractionResult node::TupleDecl::extractNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            declarations;
    }

    TypeNameExtractionResult node::TupleDecl::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractTypeNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            declarations;
    }

}

namespace esl {

    using cynth::syn::node::Declaration;
    using cynth::syn::node::TupleDecl;

    template <>
    void component_deleter<Declaration>::operator () (Declaration * ptr) const {
        delete ptr;
    }

    template <>
    Declaration * component_allocator<Declaration>::operator () (Declaration const & other) const {
        return new Declaration{other};
    }

    template <>
    Declaration * component_allocator<Declaration>::operator () (Declaration && other) const {
        return new Declaration{std::move(other)};
    }

    template <>
    void component_deleter<TupleDecl>::operator () (TupleDecl * ptr) const {
        delete ptr;
    }

    template <>
    TupleDecl * component_allocator<TupleDecl>::operator () (TupleDecl const & other) const {
        return new TupleDecl{other};
    }

    template <>
    TupleDecl * component_allocator<TupleDecl>::operator () (TupleDecl && other) const {
        return new TupleDecl{std::move(other)};
    }

}
