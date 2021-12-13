#include "syn/nodes/declarations.hpp"

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/string.hpp"

#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"

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

namespace cynth {

    namespace target = esl::target;
    using esl::lift;

    namespace {

        interface::StatementResolutionResult resolveStatementImpl (context::C & ctx, interface::node auto const & decl) {
            auto declsResult = interface::resolveDeclaration(ctx)(decl);
            if (!declsResult)
                return declsResult.error();
            auto decls = *std::move(declsResult);

            for (auto const & decl : decls) {
                auto defResult = esl::unite_results(lift<target::component_vector_tiny_result, target::category>(
                    [&ctx] (auto const & type) -> esl::result<sem::Variable> {
                        auto result = interface::translateDefinition(ctx, std::nullopt)(type);
                        if (!result) return result.error();
                        return sem::Variable{result->value};
                    }
                )(decl.type));
                if (!defResult) return defResult.error();
                auto vars = *std::move(defResult);

                auto varResult = ctx.compCtx->insertValue(decl.name, vars);
                if (!varResult) return varResult.error();
            }

            return {};
        }

    }

    //// Declaration ////

    interface::DisplayResult syn::node::Declaration::display () const {
        return lift<target::component, target::category>(interface::display)(type) + " " + interface::display(name);
    }

    interface::DeclarationResolutionResult syn::node::Declaration::resolveDeclaration (context::C & ctx) const {
        auto typeResult = lift<target::component, target::category>(
            interface::resolveType(ctx)
        )(type);
        if (!typeResult) return typeResult.error();
        auto type = *std::move(typeResult);
        return esl::init<esl::tiny_vector>(sem::CompleteDeclaration{
            esl::make_component_vector(std::move(type)),
            *name.name
        });
    }

    interface::StatementResolutionResult syn::node::Declaration::resolveStatement (context::C & ctx) const {
        return resolveStatementImpl(ctx, *this);
    }

    //// TupleDecl ////

    interface::DisplayResult syn::node::TupleDecl::display () const {
        return
            "(" +
            esl::join(", ", lift<target::component_vector, target::category>(interface::display)(declarations)) +
            ")";
    }

    interface::DeclarationResolutionResult syn::node::TupleDecl::resolveDeclaration (context::C & ctx) const {
        interface::DeclarationResolutionResult::value_type result;
        auto declsResult = esl::unite_results(lift<target::component_vector, target::category>(
            interface::resolveDeclaration(ctx)
        )(declarations));
        if (!declsResult) return declsResult.error();
        auto decls = *std::move(declsResult);
        for (auto const & tuple: decls) for (auto const & value: tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

    interface::StatementResolutionResult syn::node::TupleDecl::resolveStatement (context::C & ctx) const {
        return resolveStatementImpl(ctx, *this);
    }

}
