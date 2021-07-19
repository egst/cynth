#include "asg/targets.hpp"

#include "context_types.hpp"
#include "asg/interface.hpp"

namespace cynth {

    template <>
    void component_deleter<asg::any_target>::operator () (asg::any_target * ptr) const {
        delete ptr;
    }

    template <>
    asg::any_target * component_allocator<asg::any_target>::operator () (asg::any_target const & other) const {
        return new asg::any_target{other};
    }

    template <>
    asg::any_target * component_allocator<asg::any_target>::operator () (asg::any_target && other) const {
        return new asg::any_target{std::move(other)};
    }

    constexpr auto const_check = [] (auto const & type_tuple) {
        return util::all(lift::category_vector{util::overload {
            [] (asg::type::Const const &) {
                return false;
            },
            [] <typename Type> (Type &&) requires (!util::same_as_no_cvref<Type, asg::type::Const>) {
                return true;
            }
        }} (type_tuple));
    };

    asg::target_resolution_result asg::direct_target::resolve_target () const {
        if (!const_check(value.type))
            return result_error{"Cannot assign to a const value."};
        return typed_target_value {
            .value = value.value,
            .type  = value.type
        };
    }

    asg::target_resolution_result asg::subscript_target::resolve_target () const {
        auto nested_result = asg::resolve_target(container);
        if (!nested_result)
            return nested_result.error();
        auto nested = *std::move(nested_result);

        if (nested.value.size() == 0)
            return result_error{"Assignment by element (a[i] = x) to an uninitialized array is not supported yet."};
        if (nested.value.size() > 1)
            return result_error{"Assignment by element (a[i] = x) to a tuple of arrays is not supported yet."};

        if (location.size() == 0)
            // TODO: This is an importand feature.
            // However, it can be replaced with: a = for ($ e in b) e,
            // which may also be used in a definition: $ a = for ($ e in b) e
            return result_error{"Assignment by all elements (a[] = x) is not supported yet."};
        if (location.size() > 1)
            return result_error{"Assignment by multiple elements (a[i, j, ...] = x) is not supported yet."};

        auto & value = nested.value.front();

        auto index_result = asg::get<integral>(location.front());
        if (!index_result)
            return index_result.error();
        integral index = *index_result;

        using result_type = result<typed_target_value>;
        auto target_result = lift::category{util::overload {
            [index] (asg::value::Array & a) -> result_type {
                if (index >= a.size)
                    return result_error{"Assignment by element subscript index out of bounds."};
                if (index < 0)
                    return result_error{"Negative indices not supported yet for assignment by elements."};
                auto & ref = a.value->value[index];
                auto type = asg::value_type(ref);
                if (!const_check(type))
                    return result_error{"Cannot assign by element to an array of const values."};
                return typed_target_value {
                    .value = ref,
                    .type  = type
                };
                // TODO: the element's value_type should be the same
                // as the nested type in the value_type of the whole array,
                // but this seems like a source of potential bugs.
                // I should either change the type abstractions around this to model the situation more tightly,
                // or make sure, that the invariant (same array element type and types of individual elements)
                // is enforced.
            },
            [] (asg::value::Const const &) -> result_type {
                // Note: This should have been handled by the nested asg::resolve_target call.
                return result_error{"Cannot assign by element to a const value. (TODO: This case should never happen.)"};
            },
            [] (auto const &) -> result_type {
                return result_error{"Cannot assign by element to a non-array value."};
            }
        }} (value);

        if (!target_result)
            return target_result.error();

        return *std::move(target_result);
    }

}
