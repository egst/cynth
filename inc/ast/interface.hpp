#pragma once

#include <concepts>

#include "esl/functional.hpp"
#include "esl/result.hpp"
#include "esl/containers.hpp"

#include "util.hpp"
#include "common_interface.hpp"
#include "sem/context.hpp"
#include "sem/translation_context.hpp"
#include "ast/interface_types.hpp"

namespace cynth::ast::interface {

    template <typename Node>
    concept expression = requires (Node node, sem::Context & ctx) {
        { node.evaluate(ctx) } -> std::same_as<EvaluationResult>;
    };

    template <typename Node>
    concept statement = requires (Node node, sem::Context & ctx) {
        { node.execute(ctx) } -> std::same_as<ExecutionResult>;
    };

    template <typename Node>
    concept type = requires (Node node, sem::Context & ctx) {
        { node.evalType(ctx) } -> std::same_as<TypeEvaluationResult>;
    };

    template <typename Node>
    concept arrayElem = requires (Node node, sem::Context & ctx) {
        { node.evalArrayElem(ctx) } -> std::same_as<EvaluationResult>; // TODO: Decide on the result type.
    };

    template <typename Node>
    concept declaration = requires (Node node, sem::Context & ctx) {
        { node.evalDecl(ctx) } -> std::same_as<DeclarationEvaluationResult>;
    };

    template <typename Node>
    concept rangeDecl = requires (Node node, sem::Context & ctx) {
        { node.evalRangeDecl(ctx) } -> std::same_as<RangeDeclarationEvaluationResult>;
    };

    template <typename Node>
    concept target = requires (Node node, sem::Context & ctx) {
        { node.evalTarget(ctx) } -> std::same_as<TargetEvaluationResult>;
    };

    template <typename Node>
    concept translatable = requires (Node node, sem::TranslationContext & ctx) {
        { node.translate(ctx) } -> std::same_as<TranslationResult>;
    };

}

namespace cynth::ast {

    /**
     *  Translation of a node with the given context returns some result of the translation and modifies the context.
     *  The result is represented with `tuple_vector<result<variant<expression, value>>>` and may contain one of the following:
     *  * a string (std::string) representing a C expression
     *  * a value (sem::value::complete) representing a compile-time constant
     *  * nothing, representing a valueless statement
     *  * an error
     *  The followong may be added to the translation context:
     *  * global declarations (buffers, functions and everything in the outermost scope) to be located at the top of the file
     *  * local declarations (local arrays) to be located at the top of the current function body
     *  * helper statements (side-effects) to be appended as new lines of code in the current function body
     *  Only after the helper statements may the currently translated construct's direct translation be placed, if there is one.
     *  Also, the "compconst" context is modified accordingly.
     */
    constexpr auto translate (sem::TranslationContext & ctx) {
        return esl::overload(
            [&ctx] (interface::translatable auto const & node) -> TranslationResult {
                return node.translate(ctx);
            },
            [] <typename Node> (Node const &) -> TranslationResult {
                return esl::result_error{"This node is not directly translatable."};
            }
        );
    }

    constexpr auto execute (sem::Context & ctx) {
        return esl::overload(
            [&ctx] (interface::statement auto const & node) {
                return node.execute(ctx);
            },
            [&ctx] (interface::expression auto const & node) -> ExecutionResult {
                auto result = esl::unite_results(node.evaluate(ctx));
                if (!result)
                    return result.error();
                return {};
            }
        );
    }

    constexpr auto evaluate (sem::Context & ctx) {
        return [&ctx] <interface::expression Node> (Node const & node) {
            return node.evaluate(ctx);
        };
    }

    constexpr auto names =
        [] <typename Node> (Node const & node)
        requires (
            interface::expression <Node> ||
            interface::statement  <Node> ||
            interface::type       <Node>
        ) {
            return node.names();
        };

    constexpr auto type_names =
        [] <typename Node> (Node const & node)
        requires (
            interface::expression <Node> ||
            interface::statement  <Node> ||
            interface::type       <Node>
        ) {
            return node.typeNames();
        };

    constexpr auto evalType (sem::Context & ctx) {
        return [&ctx] (interface::type auto const & node) {
            return node.evalType(ctx);
        };
    }

    constexpr auto evalArrayElem (sem::Context & ctx) {
        return [&ctx] (interface::arrayElem auto const & node) {
            return node.evalArrayElem(ctx);
        };
    }

    constexpr auto evalDecl (sem::Context & ctx) {
        return [&ctx] (interface::declaration auto const & node) {
            return node.evalDecl(ctx);
        };
    }

    constexpr auto evalRangeDecl (sem::Context & ctx) {
        return [&ctx] (interface::rangeDecl auto const & node) {
            return node.evalRangeDecl(ctx);
        };
    }

    constexpr auto evalTarget (sem::Context & ctx) {
        return esl::overload(
            [&ctx] (interface::target auto const & node) -> TargetEvaluationResult {
                return node.evalTarget(ctx);
            },
            [] (auto const &) -> TargetEvaluationResult {
                return esl::result_error{"Assignment target may only be a name, a subscript or any tuple thereof."};
            }
        );
    }

}
