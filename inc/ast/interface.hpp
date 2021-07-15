#pragma once

#include "interface_types.hpp"
#include "lift.hpp"
#include "context.hpp"
#include "asg/values.hpp"

#include <string>
#include <variant>
#include <concepts>

namespace cynth::ast::interface {

    template <typename Node>
    concept any = requires (Node node) {
        { node.display()  } -> std::same_as<display_result>;
    };

    template <typename Node>
    concept expression = interface::any<Node> && requires (Node node, context & ctx) {
        { node.evaluate(ctx) } -> std::same_as<evaluation_result>;
    };

    template <typename Node>
    concept statement = interface::any<Node> && requires (Node node, context & ctx) {
        { node.execute(ctx) } -> std::same_as<execution_result>;
    };

    template <typename Node>
    concept type = interface::any<Node> && requires (Node node, context & ctx) {
        { node.eval_type(ctx) } -> std::same_as<type_eval_result>;
    };

    template <typename Node>
    concept array_elem = interface::any<Node> && requires (Node node, context & ctx) {
        { node.eval_array_elem(ctx) } -> std::same_as<evaluation_result>; // TODO: Decide on the result type.
    };

    template <typename Node>
    concept declaration = interface::any<Node> && requires (Node node, context & ctx) {
        { node.eval_decl(ctx) } -> std::same_as<decl_eval_result>;
    };

    template <typename Node>
    concept range_decl = interface::any<Node> && requires (Node node, context & ctx) {
        { node.eval_range_decl(ctx) } -> std::same_as<range_decl_eval_result>;
    };

}

namespace cynth::ast {

    constexpr auto display = lift::any {
        [] <interface::any Node> (Node const & node) {
            return node.display();
        }
    };

    constexpr auto execute = [] (context & ctx) {
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

    constexpr auto evaluate = [] (context & ctx) {
        return lift::any {
            [&ctx] <interface::expression Node> (Node const & node) {
                return node.evaluate(ctx);
            }
        };
    };

    constexpr auto eval_type = [] (context & ctx) {
        return lift::any {
            [&ctx] <interface::type Node> (Node const & node) {
                return node.eval_type(ctx);
            }
        };
    };

    constexpr auto eval_array_elem = [] (context & ctx) {
        return lift::any {
            [&ctx] <interface::array_elem Node> (Node const & node) {
                return node.eval_array_elem(ctx);
            }
        };
    };

    constexpr auto eval_decl = [] (context & ctx) {
        return lift::any {
            [&ctx] <interface::declaration Node> (Node const & node) {
                return node.eval_decl(ctx);
            }
        };
    };

    constexpr auto eval_range_decl = [] (context & ctx) {
        return lift::any {
            [&ctx] <interface::range_decl Node> (Node const & node) {
                return node.eval_range_decl(ctx);
            }
        };
    };

}
