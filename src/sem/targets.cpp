#include "sem/targets.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::sem::Target;

    template <>
    void component_deleter<Target>::operator () (Target * ptr) const {
        delete ptr;
    }

    template <>
    Target * component_allocator<Target>::operator () (Target const & other) const {
        return new Target{other};
    }

    template <>
    Target * component_allocator<Target>::operator () (Target && other) const {
        return new Target{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    constexpr auto const_check = [] (auto const & type_tuple) {
        return util::all(lift::category_vector{util::overload {
            [] (sem::type::Const const &) {
                return false;
            },
            [] (sem::type::In const &) {
                return false;
            },
            [] (sem::type::Out const &) {
                return false;
            },
            [] (sem::type::Function const &) {
                return false;
            },
            [] (sem::type::Buffer const &) {
                return false;
            },
            [] <typename Type> (Type &&)
            requires
                (!util::same_as_no_cvref<Type, sem::type::Const>)    &&
                (!util::same_as_no_cvref<Type, sem::type::In>)       &&
                (!util::same_as_no_cvref<Type, sem::type::Function>) &&
                (!util::same_as_no_cvref<Type, sem::type::Buffer>)
            {
                return true;
            }
        }} (type_tuple));
    };

    sem::target_res_result sem::direct_target::resolve_target (bool allow_const) const {
        return result_error{"TODO"};
        /*
        if (!allow_const && !const_check(value.type))
            return result_error{"Cannot assign to a const value."};
        return typed_target_value {
            .value = make_target_vector(value.value),
            .type  = value.type
        };
        */
    }

    using result_type = result<sem::typed_target_value>;

    constexpr auto on_non_const = [] (auto const & f) {
        return lift::category{util::overload{
            f,
            [&f] (sem::value::Const const & val) -> result_type {
                return lift::category_component{util::overload {
                    f,
                    [] (auto &&) -> result_type { // TODO: This makes no sense.
                        return result_error{"Nested const. (TODO: This should never happen.)"};
                    }
                }} (val.value);
            },
            [] <typename T> (T &&) -> result_type requires (!util::same_as_no_cvref<T, sem::value::Const> && !util::same_as_no_cvref<T, sem::value::Array>) {
                return result_error{"Cannot assign by element to a non-array value. -- " + std::string{__PRETTY_FUNCTION__}};
            }
        }};
    };

    sem::target_res_result sem::subscript_target::resolve_target (bool) const {
        // TODO: What about nested arrays (Int const? [m] const? [n] const?) and constness?
        auto nested_result = sem::resolve_const_target(container);
        if (!nested_result)
            return nested_result.error();
        auto nested = *std::move(nested_result);

        if (nested.value.size() == 0)
            return result_error{"Referential value assignment (a[...] = x) to an uninitialized value is not supported yet."};
        if (nested.value.size() > 1)
            return result_error{"Referential value assignment (a[...] = x) to a tuple of values is not supported yet."};

        auto & value = *nested.value.front();

        // TODO: Clean this up.
        // This started as an implementation only meant for arrays.
        // Later I realized that output variables behave similarly.
        auto target_result = on_non_const(util::overload {
            // TODO: How come this works with a const ref?
            [&location = location] (sem::value::Array const & a) -> result_type {
                if (location.size() == 0)
                    // TODO: This is an importand feature.
                    // However, it can be replaced with: a = for ($ e in b) e,
                    // which may also be used in a definition: $ a = for ($ e in b) e
                    return result_error{"Referential value assignmet into all array elements (a[] = x) is not supported yet."};
                if (location.size() > 1)
                    return result_error{"Referential value assignmet into multiple array elements (a[i, j, ...] = x) is not supported yet."};
                auto index_result = sem::get<integral>(location.front());
                if (!index_result)
                    return index_result.error();
                integral index = *index_result;

                if (index >= a.size)
                    return result_error{"Referential value assignment index out of bounds."};
                if (index < 0)
                    return result_error{"Negative indices not supported yet for referential value assignment."};
                auto & ref = a.value->value[index];
                //auto type = sem::value_type(ref);
                tuple_vector<type::complete> type = a.type;
                if (!const_check(type))
                    return result_error{"Cannot perform a referential value assignment on an array of const values."};
                return typed_target_value {
                    .value = make_target_vector(ref),
                    .type  = std::move(type)
                };
                // TODO: the element's value_type should be the same
                // as the nested type in the value_type of the whole array,
                // but this seems like a source of potential bugs.
                // I should either change the type abstractions around this to model the situation more tightly,
                // or make sure, that the invariant (same array element type and types of individual elements)
                // is enforced.
            },
            [&location = location] (sem::value::Out const & o) -> result_type {
                if (location.size() != 0)
                    return result_error{"Referential value assignmet into non-array types (out) must only use an empty location list (a[] = x)."};
                return typed_target_value {
                    .value = make_target_vector(*o.value->value),
                    .type  = make_type_vector(*o.type)
                };
            }
        }) (value);

        if (!target_result)
            return target_result.error();

        return *std::move(target_result);
    }

}
#endif
