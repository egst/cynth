#pragma once

#include "lift.hpp"
#include "interface_types.hpp"
#include "common_interface.hpp"
#include "sem/context.hpp"
#include "sem/translation_context.hpp"
#include "sem/values.hpp"

#include <string>
#include <variant>
#include <concepts>

namespace cynth::ast::interface {

    template <typename Node>
    concept any = cynth::interface::displayable<Node>;

    template <typename Node>
    concept expression = interface::any<Node> && requires (Node node, sem::context & ctx) {
        { node.evaluate(ctx) } -> std::same_as<evaluation_result>;
    };

    template <typename Node>
    concept statement = interface::any<Node> && requires (Node node, sem::context & ctx) {
        { node.execute(ctx) } -> std::same_as<execution_result>;
    };

    template <typename Node>
    concept type = interface::any<Node> && requires (Node node, sem::context & ctx) {
        { node.eval_type(ctx) } -> std::same_as<type_eval_result>;
    };

    template <typename Node>
    concept array_elem = interface::any<Node> && requires (Node node, sem::context & ctx) {
        { node.eval_array_elem(ctx) } -> std::same_as<evaluation_result>; // TODO: Decide on the result type.
    };

    template <typename Node>
    concept declaration = interface::any<Node> && requires (Node node, sem::context & ctx) {
        { node.eval_decl(ctx) } -> std::same_as<decl_eval_result>;
    };

    template <typename Node>
    concept range_decl = interface::any<Node> && requires (Node node, sem::context & ctx) {
        { node.eval_range_decl(ctx) } -> std::same_as<range_decl_eval_result>;
    };

    template <typename Node>
    concept target = interface::any<Node> && requires (Node node, sem::context & ctx) {
        { node.eval_target(ctx) } -> std::same_as<target_eval_result>;
    };

    template <typename Node>
    concept translatable = requires (Node node, sem::translation_context & ctx) {
        { node.translate(ctx) } -> std::same_as<translation_result>;
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
    constexpr auto translate = [] (sem::translation_context & ctx) {
        return lift::any{util::overload {
            [&ctx] <interface::translatable Node> (Node const & node) -> translation_result {
                return node.translate(ctx);
            },
            [] <interface::any Node> (Node const &) -> translation_result requires (!interface::translatable<Node>) {
                return make_translation_result(result_error{"This node is not directly translatable."});
            }
        }};
    };

    constexpr auto execute = [] (sem::context & ctx) {
        return lift::any{util::overload {
            [&ctx] <interface::statement Node> (Node const & node) {
                return node.execute(ctx);
            },
            [&ctx] <interface::expression Node> (Node const & node) -> execution_result
            requires (!interface::statement<Node>) {
                auto result = util::unite_results(node.evaluate(ctx));
                if (!result)
                    return result.error();
                return {};
            }
        }};
    };

    constexpr auto evaluate = [] (sem::context & ctx) {
        return lift::any {
            [&ctx] <interface::expression Node> (Node const & node) {
                return node.evaluate(ctx);
            }
        };
    };

    constexpr auto names = lift::any {
        [] <typename Node> (Node const & node)
        requires (
            interface::expression <Node> ||
            interface::statement  <Node> ||
            interface::type       <Node>
        ) {
            return node.names();
        }
    };

    constexpr auto type_names = lift::any {
        [] <typename Node> (Node const & node)
        requires (
            interface::expression <Node> ||
            interface::statement  <Node> ||
            interface::type       <Node>
        ) {
            return node.type_names();
        }
    };

    constexpr auto eval_type = [] (sem::context & ctx) {
        return lift::any {
            [&ctx] <interface::type Node> (Node const & node) {
                return node.eval_type(ctx);
            }
        };
    };

    constexpr auto eval_array_elem = [] (sem::context & ctx) {
        return lift::any {
            [&ctx] <interface::array_elem Node> (Node const & node) {
                return node.eval_array_elem(ctx);
            }
        };
    };

    constexpr auto eval_decl = [] (sem::context & ctx) {
        return lift::any {
            [&ctx] <interface::declaration Node> (Node const & node) {
                return node.eval_decl(ctx);
            }
        };
    };

    constexpr auto eval_range_decl = [] (sem::context & ctx) {
        return lift::any {
            [&ctx] <interface::range_decl Node> (Node const & node) {
                return node.eval_range_decl(ctx);
            }
        };
    };

    constexpr auto eval_target = [] (sem::context & ctx) {
        return lift::any{util::overload {
            [&ctx] <interface::any Node> (Node const & node) -> target_eval_result requires interface::target<Node> {
                return node.eval_target(ctx);
            },
            [] <interface::any Node> (Node const &) -> target_eval_result requires (!interface::target<Node>) {
                return result_error{"Assignment target may only be a name, a subscript or any tuple thereof."};
            },
        }};
    };

}
