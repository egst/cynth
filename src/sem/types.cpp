#include "sem/types.hpp"

#include "config.hpp"
#include "lift2.hpp"
#include "component.hpp"
#include "common_interface.hpp"
#include "sem/interface.hpp"
#include "sem/declarations.hpp"
#include "sem/util.hpp"
#include "util/general.hpp"
#include "util/container.hpp"

#include <string>

namespace cynth {

    //// Forward declarations/instantiations ////

    /*
    template sem::common_type_result sem::type::const_type    <true>::common(sem::type::Const    const &) const;
    template sem::common_type_result sem::type::array_type    <true>::common(sem::type::Array    const &) const;
    template sem::common_type_result sem::type::buffer_type   <true>::common(sem::type::Buffer   const &) const;
    template sem::common_type_result sem::type::function_type <true>::common(sem::type::Function const &) const;

    template bool sem::type::in_type       <true>::same(sem::type::In       const &) const;
    template bool sem::type::out_type      <true>::same(sem::type::Out      const &) const;
    template bool sem::type::const_type    <true>::same(sem::type::Const    const &) const;
    template bool sem::type::array_type    <true>::same(sem::type::Array    const &) const;
    template bool sem::type::buffer_type   <true>::same(sem::type::Buffer   const &) const;
    template bool sem::type::function_type <true>::same(sem::type::Function const &) const;
    */

    //// Categories ////

    template <>
    void component_deleter<sem::type::complete>::operator () (sem::type::complete * ptr) const {
        delete ptr;
    }

    template <>
    sem::type::complete * component_allocator<sem::type::complete>::operator () (sem::type::complete const & other) const {
        return new sem::type::complete{other};
    }

    template <>
    sem::type::complete * component_allocator<sem::type::complete>::operator () (sem::type::complete && other) const {
        return new sem::type::complete{std::move(other)};
    }

    template <>
    void component_deleter<sem::type::incomplete>::operator () (sem::type::incomplete * ptr) const {
        delete ptr;
    }

    template <>
    sem::type::incomplete * component_allocator<sem::type::incomplete>::operator () (sem::type::incomplete const & other) const {
        return new sem::type::incomplete{other};
    }

    template <>
    sem::type::incomplete * component_allocator<sem::type::incomplete>::operator () (sem::type::incomplete && other) const {
        return new sem::type::incomplete{std::move(other)};
    }

    //// Bool ////

    display_result sem::type::Bool::display () const {
        return "Bool";
    }

    /** `cth_t_Bool` */
    sem::type_transl_result sem::type::Bool::transl_type () const {
        return string{} + global_prefix + "_" + type_prefix + "_Bool";
    }

    sem::common_type_result sem::type::Bool::common (sem::type::Bool const &) const {
        return {sem::type::Bool{}};
    }

    sem::common_type_result sem::type::Bool::common (sem::type::Int const &) const {
        return {sem::type::Int{}};
    }

    sem::common_type_result sem::type::Bool::common (sem::type::Float const &) const {
        return {sem::type::Float{}};
    }

    sem::common_type_result sem::type::Bool::common (sem::type::In const & other) const {
        return sem::common(*this)(other.type);
    }

    sem::common_type_result sem::type::Bool::common (sem::type::Const const & other) const {
        return sem::common(*this)(other.type);
    }

    bool sem::type::Bool::same (sem::type::Bool const &) const {
        return true;
    }

    //// Int ////

    display_result sem::type::Int::display () const {
        return "Int";
    }

    /** `cth_t_Int` */
    sem::type_transl_result sem::type::Int::transl_type () const {
        return string{} + global_prefix + "_" + type_prefix + "_Int";
    }

    sem::common_type_result sem::type::Int::common (sem::type::Int const &) const {
        return {sem::type::Int{}};
    }

    sem::common_type_result sem::type::Int::common (sem::type::Float const &) const {
        return {sem::type::Float{}};
    }

    sem::common_type_result sem::type::Int::common (sem::type::In const & other) const {
        return sem::common(*this)(other.type);
    }

    sem::common_type_result sem::type::Int::common (sem::type::Const const & other) const {
        return sem::common(*this)(other.type);
    }

    bool sem::type::Int::same (sem::type::Int const &) const {
        return true;
    }

    //// Float ////

    display_result sem::type::Float::display () const {
        return "Float";
    }

    /** `cth_t_Float` */
    sem::type_transl_result sem::type::Float::transl_type () const {
        return string{} + global_prefix + "_" + type_prefix + "_Float";
    }

    sem::common_type_result sem::type::Float::common (sem::type::Float const &) const {
        return {sem::type::Float{}};
    }

    sem::common_type_result sem::type::Float::common (sem::type::In const & other) const {
        return sem::common(*this)(other.type);
    }

    sem::common_type_result sem::type::Float::common (sem::type::Const const & other) const {
        return sem::common(*this)(other.type);
    }

    bool sem::type::Float::same (sem::type::Float const &) const {
        return true;
    }

    //// String ////

    display_result sem::type::String::display () const {
        return "String";
    }

    /** `cth_t_String` */
    sem::type_transl_result sem::type::String::transl_type () const {
        return string{} + global_prefix + "_" + type_prefix + "_String";
    }

    sem::common_type_result sem::type::String::common (sem::type::String const &) const {
        return {sem::type::String{}};
    }

    bool sem::type::String::same (sem::type::String const &) const {
        return true;
    }

    //// In ////

    template <>
    display_result sem::type::In::display () const {
        return "T in"; // TODO
    }

    /** `T` */
    template <>
    sem::type_transl_result sem::type::In::transl_type () const {
        return lift2<component, target::category>(sem::transl_type)(type);
    }

    template <bool Complete>
    sem::decay_result sem::type::in_type<Complete>::decay () const requires Complete {
        return *type;
    }
    template sem::decay_result sem::type::in_type<true>::decay () const;

    template <bool Complete>
    bool sem::type::in_type<Complete>::same (sem::type::In const & other) const requires Complete {
        return sem::same(type, other.type);
    }
    template bool sem::type::in_type<true>::same (sem::type::In const & other) const;

    template <bool Complete>
    sem::complete_result sem::type::in_type<Complete>::complete (context & ctx) const requires (!Complete) {
        auto result = sem::complete(ctx)(type);
        if (!result)
            return result.error();
        return {sem::type::In {
            .type = *result
        }};
    }
    template sem::complete_result sem::type::in_type<false>::complete (context &) const;

    //// Out ////

    template <>
    display_result sem::type::Out::display () const {
        return "T out"; // TODO
    }

    /** `T` */
    template <>
    sem::type_transl_result sem::type::Out::transl_type () const {
        return lift2<component, target::category>(sem::transl_type)(type);
    }

    template <bool Complete>
    sem::decay_result sem::type::out_type<Complete>::decay () const requires Complete {
        return *type;
    }
    template sem::decay_result sem::type::out_type<true>::decay () const;

    template <bool Complete>
    bool sem::type::out_type<Complete>::same (sem::type::Out const & other) const requires Complete {
        return sem::same(type, other.type);
    }
    template bool sem::type::out_type<true>::same (sem::type::Out const & other) const;

    template <bool Complete>
    sem::complete_result sem::type::out_type<Complete>::complete (context & ctx) const requires (!Complete) {
        auto result = sem::complete(ctx)(type);
        if (!result)
            return result.error();
        return {sem::type::Out {
            .type = *result
        }};
    }
    template sem::complete_result sem::type::out_type<false>::complete (context &) const;

    //// Const ////

    template <>
    display_result sem::type::Const::display () const {
        return "T const"; // TODO
    }

    /** `T const` */
    template <>
    sem::type_transl_result sem::type::Const::transl_type () const {
        auto result = lift2<component, target::category>(sem::transl_type)(type);
        if (!result)
            return result.error();
        return *result + " const";
    }

    template <bool Complete>
    sem::decay_result sem::type::const_type<Complete>::decay () const requires Complete {
        return *type;
    }
    template sem::decay_result sem::type::const_type<true>::decay () const;

    template <bool Complete>
    sem::common_type_result sem::type::const_type<Complete>::common (sem::type::Const const & other) const requires Complete {
        auto result = sem::common(type, other.type);
        if (!result)
            return result.error();
        return {sem::type::Const {
            .type = *result
        }};
    }
    template sem::common_type_result sem::type::const_type<true>::common (sem::type::Const const & other) const;

    template <bool Complete>
    bool sem::type::const_type<Complete>::same (sem::type::Const const & other) const requires Complete {
        return sem::same(type, other.type);
    }
    template bool sem::type::const_type<true>::same (sem::type::Const const & other) const;

    template <bool Complete>
    sem::complete_result sem::type::const_type<Complete>::complete (context & ctx) const requires (!Complete) {
        auto result = sem::complete(ctx)(type);
        if (!result)
            return result.error();
        return {sem::type::Const {
            .type = *result
        }};
    }
    template sem::complete_result sem::type::const_type<false>::complete (context &) const;

    //// Array ////

    result<sem::type::Array> sem::type::make_array (component_vector<type::complete> && type, integral size) {
        if (size <= 0)
            return result_error{"Array must have a positive size."};
        auto elem_type_check = util::unite_results(sem::array_elem_type_check(type));
        if (!elem_type_check)
            return elem_type_check.error();
        return sem::type::Array {
            .type = std::move(type),
            .size = size
        };
    }

    template <>
    display_result sem::type::Array::display () const {
        return "T [n]"; // TODO
    }

    /** `T *` */
    template <>
    sem::type_transl_result sem::type::Array::transl_type () const {
        auto transl_result = lift2<result, target::category>(sem::transl_type)(util::single(type));
        if (!transl_result)
            return transl_result.error();
        return *transl_result + " *";
    }

    template <bool Complete> sem::common_type_result
    sem::type::array_type<Complete>::common (sem::type::Array const & other) const requires Complete {
        auto results = (lift2<component, target::category>(
            [] <typename T, typename U> (T const & a, U const & b) -> std::optional<sem::type::complete> {
            //requires (std::same_as<T, U> || !std::same_as<T, sem::type::Const> && std::same_as<U, sem::type::Const>)
                if (sem::same(a, b))
                    return {a};
                return {};
            },
            [] <typename T> (sem::type::Const const & a, T const & b) -> std::optional<sem::type::complete>
            requires (!std::same_as<T, sem::type::Const>) {
                if (sem::same(a, b))
                    return {a};
                if (sem::same(a, sem::type::Const{{b}}))
                    return {sem::type::Const{{a}}};
                return {};
            },
            [] <typename T> (T const & a, sem::type::Const const & b) -> std::optional<sem::type::complete>
            requires (!std::same_as<T, sem::type::Const>) {
                if (sem::same(a, b))
                    return {a};
                if (sem::same(sem::type::Const{{a}}, b))
                    return {sem::type::Const{{a}}};
                return {};
            }
        )(type, other.type));
        if (!results)
            return results.error();
        auto result = util::unite_optionals(*results);
        if (!result)
            return result_error{"No common type for two arrays because of mismatched elements type."};
        auto array_result = sem::type::make_array(
            make_component_vector(*result),
            std::min(size, other.size)
        );
        if (!array_result)
            return array_result.error();
        return {*array_result};
    }
    template sem::common_type_result sem::type::array_type<true>::common (sem::type::Array const & other) const;

    template <bool Complete>
    bool sem::type::array_type<Complete>::same (sem::type::Array const & other) const requires Complete {
        auto result = sem::same(type, other.type);
        if (!result)
            return false;
        return
            size == other.size &&
            util::all(*result);
    }
    template bool sem::type::array_type<true>::same (sem::type::Array const & other) const;

    template <bool Complete>
    sem::complete_result sem::type::array_type<Complete>::complete (context & ctx) const requires (!Complete) {
        auto type_result = util::unite_results(sem::complete(ctx)(type));
        if (!type_result)
            return type_result.error();

        auto size_result = lift2<component, target::category>(
            [] (value::unknown const &) -> result<int> {
                return result_error{"Unknown array size."};
            },
            [&ctx] <sem::interface::value Value> (Value const & value) -> result<int> {
                return sem::get<integral>(sem::convert(ctx)(sem::type::Int{})(value));
            }
        )(size);
        if (!size_result)
            return size_result.error();

        auto array_result = sem::type::make_array(
            make_component_vector(*type_result),
            *size_result
        );
        if (!array_result)
            return array_result.error();
        return {*array_result};
    }
    template sem::complete_result sem::type::array_type<false>::complete (context &) const;

    //// Buffer ////

    result<sem::type::Buffer> sem::type::make_buffer (integral size) {
        if (size <= 0)
            return result_error{"Buffer must have a positive size."};
        return sem::type::Buffer {
            .size = size
        };
    }

    /** `float *` */
    template <>
    sem::type_transl_result sem::type::Buffer::transl_type () const {
        // This assumes that type::Float always returns a non-error value.
        return *sem::type::Float{}.transl_type() + " *";
    }

    template <>
    display_result sem::type::Buffer::display () const {
        return "buffer [n]"; // TODO
    }

    template <bool Complete>
    sem::common_type_result sem::type::buffer_type<Complete>::common (sem::type::Buffer const & other) const requires Complete {
        if (size != other.size)
            return result_error{"No common type for two buffers because of different sizes."};
        return {*this};
    }
    template sem::common_type_result sem::type::buffer_type<true>::common (sem::type::Buffer const & other) const;

    template <bool Complete>
    bool sem::type::buffer_type<Complete>::same (sem::type::Buffer const & other) const requires Complete {
        return size == other.size;
    }
    template bool sem::type::buffer_type<true>::same (sem::type::Buffer const & other) const;

    template <bool Complete>
    sem::complete_result sem::type::buffer_type<Complete>::complete (context & ctx) const requires (!Complete) {
        auto size_result = lift2<component, target::category>(
            [] (value::unknown const &) -> result<integral> {
                return result_error{"Unknown array size."};
            },
            [&ctx] <sem::interface::value Value> (Value const & value) -> result<integral> {
                return sem::get<integral>(sem::convert(ctx)(sem::type::Int{})(value));
            }
        )(size);
        if (!size_result)
            return size_result.error();

        auto buffer_result = sem::type::make_buffer(*size_result);
        if (!buffer_result)
            return buffer_result.error();

        return {*buffer_result};
    }
    template sem::complete_result sem::type::buffer_type<false>::complete (context &) const;

    //// Function ////

    template <>
    display_result sem::type::Function::display () const {
        return "Output (Input)"; // TODO
    }

    template <>
    sem::type_transl_result sem::type::Function::transl_type () const {
        return result_error{"Function types are not directly translatable."};
    }

    template <bool Complete>
    sem::common_type_result sem::type::function_type<Complete>::common (sem::type::Function const & other) const requires Complete {
        auto out_result = sem::same(out, other.out);
        if (!out_result)
            return out_result.error();
        if (!util::all(*out_result))
            return result_error{"No common type for two functions because of diferent output types."};
        auto in_result = sem::same(in, other.in);
        if (!in_result)
            return in_result.error();
        if (!util::all(*in_result))
            return result_error{"No common type for two functions because of diferent input types."};
        return {*this};
    }
    template sem::common_type_result sem::type::function_type<true>::common (sem::type::Function const & other) const;

    template <bool Complete>
    bool sem::type::function_type<Complete>::same (sem::type::Function const & other) const requires Complete {
        auto out_result = sem::same(out, other.out);
        auto in_result  = sem::same(in,  other.in);
        return
            out_result && util::all(*out_result) &&
            in_result  && util::all(*in_result);
    }
    template bool sem::type::function_type<true>::same (sem::type::Function const & other) const;

    template <bool Complete>
    sem::complete_result sem::type::function_type<Complete>::complete (context & ctx) const requires (!Complete) {
        auto out_result = util::unite_results(sem::complete(ctx)(out));
        if (!out_result)
            return out_result.error();
        auto in_result = util::unite_results(sem::complete(ctx)(in));
        if (!in_result)
            return in_result.error();
        return {sem::type::Function {
            .out = *out_result,
            .in  = *in_result,
        }};
    }
    template sem::complete_result sem::type::function_type<false>::complete (context &) const;

}
