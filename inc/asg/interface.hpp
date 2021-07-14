#pragma once

#include "lift.hpp"
#include "result.hpp"
#include "asg/values.hpp"
#include "asg/types.hpp"
#include "asg/declarations.hpp"
#include "ast/interface_types.hpp"
#include "util/general.hpp"
#include "util/string.hpp"
#include "util/container.hpp"

#include <concepts>

namespace cynth::asg::interface {

    template <typename Node>
    concept value = util::variant_member<Node, value::complete::variant>;

    template <typename Node, typename To>
    concept convertible = requires (Node node, To const & to) {
        { node.convert(to) } -> std::same_as<conversion_result>;
    };

    template <typename Node>
    concept typed = requires (Node node) {
        { node.value_type() } -> std::same_as<value_type_result>;
    };

    template <typename Node, typename Out>
    concept value_of = requires (Node node) {
        { node.get() } -> std::same_as<get_result<Out>>;
    };

    template <typename Node>
    concept type = util::variant_member<Node, type::complete::variant>;

    template <typename Node>
    concept decaying = requires (Node node) {
        { node.decay() } -> std::same_as<decay_result>;
    };

    template <typename Node, typename As>
    concept same = requires (Node node, As const & as) {
        { node.same(as) } -> std::same_as<bool>;
    };

    template <typename Node, typename With>
    concept common = requires (Node node, With const & type) {
        { node.common(type) } -> std::same_as<common_type_result>;
    };

    template <typename Node>
    concept incomplete_type = util::variant_member<Node, type::incomplete::variant>;

    template <typename Node>
    concept completable_type = requires (Node node) {
        { node.complete() } -> std::same_as<complete_result>;
    };

    template <typename Node>
    concept displayable = requires (Node node) {
        { node.display() } -> std::same_as<std::string>;
    };

}

namespace cynth::asg {

    namespace detail {

        constexpr auto display = [] <interface::displayable Node> (Node const & a) -> std::string {
            return a.display();
        };

    }

    // TODO: This is practically the same as ast::display.
    // Maybe it should be a more generic thing.
    constexpr auto display = lift::any {
        detail::display
    };

    namespace detail {

        template <typename Node>
        concept displayable_tuple = requires (Node node) {
            { asg::display(node) } -> util::range_of<std::string>;
        };

    }

    constexpr auto display_tuple = [] <detail::displayable_tuple Tuple> (Tuple const & a) -> std::string {
        return util::parenthesized(util::join(", ", display(a)));
    };

    // In the following docblock comments, the construct any<T>
    // means any abstraction, that is supported by lift::any.
    // f (any<T>, any<T>) means that to completely unwrap any one of them,
    // a series of the same lift::* operations must be applied.
    // E.g. f(std::variant<int, float>, std::variant<int, bool>) is ok,
    // but f(std::vector<int>, std::variant<int>) is not.

    /**
     *  value_type (any<interface::value> value) -> type::complete
     */
    constexpr auto value_type = lift::any {
        [] <interface::typed Node> (Node const & node) {
            return node.value_type();
        }
    };

    /**
     *  get <Out> (any<interface::value> value) -> result<Out>
     */
    template <typename Out>
    constexpr auto get = lift::any{util::overload {
        [] <interface::value_of<Out> Node> (Node const & node) -> get_result<Out> {
            return node.get();
        },
        [] <interface::value Node> (Node const &) -> get_result<Out> requires (!interface::value_of<Node, Out>) {
            return result_error{"Value does not contain the requested type."};
        },
    }};

    /**
     *  same (interface::type type) (any<interface::type> to) -> bool
     *  same (any<interface::type> type, any<interface::type> to) -> bool
     *
     *  TODO: Maybe I should enforce that the same method may only be called on the same type.
     *  (Two types may be "same" only if they are represented by the same C++ type.)
     */
    constexpr auto same = lift::any_asymetric{util::overload {
        [] <interface::type Node, interface::type As> (Node const & node, As const & as) requires (interface::same<Node, As>) {
            return node.same(as);
        },
        [] <interface::type Node, interface::type As> (Node const &, As const &) requires (!interface::same<Node, As>) {
            return false;
        }
    }};

    /**
     *  decay (any<interface::type> type) -> optional<type::complete>
     *  TODO: Maybe it would be better to return the same type for non-decaying types?
     */
    constexpr auto decay = lift::any{util::overload {
        [] <interface::type Node> (Node const & node) requires (interface::decaying<Node>) {
            return std::optional<decay_result>{node.decay()};
        },
        [] <interface::type Node> (Node const &) requires (!interface::decaying<Node>) {
            return std::optional<decay_result>{};
        }
    }};

    /**
     *  Shorthand for same(decay(type), to).
     *
     *  decays (interface::type type) (any<interface::type> to) -> bool
     *  decays (any<interface::type> type, any<interface::type> to) -> bool
     */
    constexpr auto decays = lift::any_asymetric{util::overload {
        [] <interface::type Node, interface::type To> (Node const & node, To const & to) requires (interface::decaying<Node>) {
            return same(to)(node.decay());
        },
        [] <interface::type Node, interface::type To> (Node const &, To const &) requires (!interface::decaying<Node>) {
            return false;
        }
    }};

    /**
     *  common (interface::type a) (any<interface::type> b) -> optional<type::complete>
     *  common (any<interface::type> a, any<interface::type> b) -> optional<type::complete>
     *
     *  This operation is symetric.
     *  It is enough to only provide one implementation for both directions.
     */
    constexpr auto common = lift::any_asymetric{util::overload {
        [] <interface::type Node> (Node const & node, Node const & with)
        requires interface::common<Node, Node> {
            return node.common(with);
        },
        [] <interface::type Node, interface::type With> (Node const & node, With const & with)
        requires (!std::same_as<Node, With>) && interface::common<Node, With> && (!interface::common<With, Node>) {
            return node.common(with);
        },
        [] <interface::type Node, interface::type With> (Node const & node, With const & with)
        requires (!std::same_as<Node, With>) && (!interface::common<Node, With>) && interface::common<With, Node> {
            return with.common(node);
        },
        [] <interface::type Node, interface::type With> (Node const &, With const &)
        requires /*(!std::same_as<Node, With>) &&*/ (!interface::common<Node, With>) && (!interface::common<With, Node>) {
            return common_type_result{result_error{"No comomn type."}};
        },
        // TODO: This problem should be caught at compile-time.
        [] <interface::type Node, interface::type With> (Node const &, With const &)
        requires /*(!std::same_as<Node, With>) &&*/ interface::common<Node, With> && interface::common<With, Node> {
            return common_type_result{result_error{"Two-way node.common(with) implementation found."}};
        }
    }};

    /**
     *  convert (interface::type to) (any<interface::value> value) -> result<value::complete>
     *  convert (any<interface::type> to, any<interface::value> value) -> result<value::complete>
     */
    constexpr auto convert = lift::any_asymetric{util::overload {
        [] <interface::type To, interface::value Node> (Node const & node, To const & to) requires (interface::convertible<Node, To>) {
            return node.convert(to);
        },
        [] <interface::type To, interface::value Node> (Node const &, To const &) requires (!interface::convertible<Node, To>) {
            return result<value::complete>{result_error{"No conversion available."}};
        }
    }};

    /**
     *  convert_to (any<interface::value> value) (interface::type to) -> result<value::complete>
     *  convert_to (any<interface::value> value, any<interface::type> to) -> result<value::complete>
     */
    constexpr auto convert_to = lift::any_asymetric{util::overload {
        [] <interface::type To, interface::value Node> (To const & to, Node const & node) requires (interface::convertible<Node, To>) {
            return node.convert(to);
        },
        [] <interface::type To, interface::value Node> (To const &, Node const &) requires (!interface::convertible<Node, To>) {
            return result<value::complete>{result_error{"No conversion available."}};
        }
    }};

    namespace detail {

        constexpr auto make_type_complete = util::overload {
            [] <interface::type Node> (Node && node) -> complete_result {
                return type::complete{std::forward<Node>(node)};
            },
            [] <interface::incomplete_type Node> (Node const & node) -> complete_result requires interface::completable_type<Node> {
                return node.complete();
            },
            [] (type::unknown const &) -> complete_result {
                return {result_error{"An unknown type ($ or type T) is not complete."}};
            }
            /*[] <interface::incomplete_type Node> (Node const &) -> complete_result requires (!interface::completable_type<Node>) {
                return {result_error{"Complete type expected."}};
            }*/
        };


        constexpr auto make_decl_complete = util::overload {
            [] <util::same_as_no_cvref<incomplete_decl> Decl> (Decl && decl) -> result<complete_decl> {
                auto complete = util::unite_results(lift::category_component{detail::make_type_complete}(util::forward_like<Decl>(decl.type)));
                if (!complete)
                    return complete.error();
                return complete_decl {
                    .type = *std::move(complete),
                    .name = decl.name
                };
            },
            [] <util::same_as_no_cvref<complete_decl> Decl> (Decl && decl) -> result<complete_decl> {
                return std::forward<Decl>(decl);
            }
        };

        constexpr auto make_range_decl_complete = util::overload {
            [] <util::same_as_no_cvref<incomplete_range_decl> Decl> (Decl && decl) -> result<complete_range_decl> {
                auto complete = util::unite_results(lift::category_component{detail::make_decl_complete}(util::forward_like<Decl>(decl.declaration)));
                if (!complete)
                    return complete.error();
                return complete_range_decl {
                    .declaration = *std::move(complete),
                    .range       = decl.range
                };
            },
            [] <util::same_as_no_cvref<complete_range_decl> Decl> (Decl && decl) -> result<complete_range_decl> {
                return std::forward<Decl>(decl);
            }
        };

    }

    constexpr auto complete = lift::any{util::overload {
        detail::make_type_complete,
        detail::make_decl_complete,
        detail::make_range_decl_complete
    }};

    // TODO: It would probably be better to write this out manually.
    constexpr auto incomplete = lift::any{util::overload {
        [] <interface::type Type> (Type && type) -> result<type::incomplete> {
            return asg::type::incomplete{asg::type::complete{std::forward<Type>(type)}};
        },
        /*[] <interface::incomplete_type Type> (Type && type) -> result<type::incomplete> {
            return asg::type::incomplete{std::forward<Type>(type)};
        },*/
        [] <interface::value Type> (Type && type) -> result<value::incomplete> {
            return asg::value::incomplete{std::forward<Type>(type)};
        }
        // ... TODO declaration?
    }};

    constexpr auto decl_type = util::overload {
        [] <util::same_as_no_cvref<complete_decl> Decl> (Decl && decl) -> tuple_vector<type::complete> {
            return util::forward_like<Decl>(decl.type);
        },
        [] <util::same_as_no_cvref<incomplete_decl> Decl> (Decl && decl) -> tuple_vector<type::incomplete> {
            return util::forward_like<Decl>(decl.type);
        },
        [] <util::range_of<complete_decl> Decls> (Decls && decls) -> tuple_vector<type::complete> {
            tuple_vector<type::complete> result;
            for (auto & decl : decls) for (auto & type : decl.type) {
                result.push_back(util::forward_like<Decls>(type));
            }
            return result;
        },
        [] <util::range_of<incomplete_decl> Decls> (Decls && decls) -> tuple_vector<type::incomplete> {
            tuple_vector<type::incomplete> result;
            for (auto & decl : decls) for (auto & type : decl.type) {
                result.push_back(util::forward_like<Decls>(type));
            }
            return result;
        }
    };

}
