#include "asg/types.hpp"

#include "asg/interface.hpp"
#include "asg/declarations.hpp"
#include "component.hpp"
#include "util/general.hpp"
#include "util/container.hpp"

#include <string>

namespace cynth {

    //// Forward declarations/instantiations ////

    /*
    template asg::common_type_result asg::type::const_type    <true>::common(asg::type::Const    const &) const;
    template asg::common_type_result asg::type::array_type    <true>::common(asg::type::Array    const &) const;
    template asg::common_type_result asg::type::buffer_type   <true>::common(asg::type::Buffer   const &) const;
    template asg::common_type_result asg::type::function_type <true>::common(asg::type::Function const &) const;

    template bool asg::type::in_type       <true>::same(asg::type::In       const &) const;
    template bool asg::type::out_type      <true>::same(asg::type::Out      const &) const;
    template bool asg::type::const_type    <true>::same(asg::type::Const    const &) const;
    template bool asg::type::array_type    <true>::same(asg::type::Array    const &) const;
    template bool asg::type::buffer_type   <true>::same(asg::type::Buffer   const &) const;
    template bool asg::type::function_type <true>::same(asg::type::Function const &) const;
    */

    //// Categories ////

    template <>
    void component_deleter<asg::type::complete>::operator () (asg::type::complete * ptr) const {
        delete ptr;
    }

    template <>
    asg::type::complete * component_allocator<asg::type::complete>::operator () (asg::type::complete const & other) const {
        return new asg::type::complete{other};
    }

    template <>
    asg::type::complete * component_allocator<asg::type::complete>::operator () (asg::type::complete && other) const {
        return new asg::type::complete{std::move(other)};
    }

    template <>
    void component_deleter<asg::type::incomplete>::operator () (asg::type::incomplete * ptr) const {
        delete ptr;
    }

    template <>
    asg::type::incomplete * component_allocator<asg::type::incomplete>::operator () (asg::type::incomplete const & other) const {
        return new asg::type::incomplete{other};
    }

    template <>
    asg::type::incomplete * component_allocator<asg::type::incomplete>::operator () (asg::type::incomplete && other) const {
        return new asg::type::incomplete{std::move(other)};
    }

    //// Bool ////

    std::string asg::type::Bool::display () const {
        return "Bool"; // TODO
    }

    asg::common_type_result asg::type::Bool::common (asg::type::Bool const &) const {
        return {asg::type::Bool{}};
    }

    asg::common_type_result asg::type::Bool::common (asg::type::Int const &) const {
        return {asg::type::Int{}};
    }

    asg::common_type_result asg::type::Bool::common (asg::type::Float const &) const {
        return {asg::type::Float{}};
    }

    asg::common_type_result asg::type::Bool::common (asg::type::In const & other) const {
        return asg::common(*this)(other.type);
    }

    asg::common_type_result asg::type::Bool::common (asg::type::Const const & other) const {
        return asg::common(*this)(other.type);
    }

    bool asg::type::Bool::same (asg::type::Bool const &) const {
        return true;
    }

    //// Int ////

    std::string asg::type::Int::display () const {
        return "Int";
    }

    asg::common_type_result asg::type::Int::common (asg::type::Int const &) const {
        return {asg::type::Int{}};
    }

    asg::common_type_result asg::type::Int::common (asg::type::Float const &) const {
        return {asg::type::Float{}};
    }

    asg::common_type_result asg::type::Int::common (asg::type::In const & other) const {
        return asg::common(*this)(other.type);
    }

    asg::common_type_result asg::type::Int::common (asg::type::Const const & other) const {
        return asg::common(*this)(other.type);
    }

    bool asg::type::Int::same (asg::type::Int const &) const {
        return true;
    }

    //// Float ////

    std::string asg::type::Float::display () const {
        return "Float";
    }

    asg::common_type_result asg::type::Float::common (asg::type::Float const &) const {
        return {asg::type::Float{}};
    }

    asg::common_type_result asg::type::Float::common (asg::type::In const & other) const {
        return asg::common(*this)(other.type);
    }

    asg::common_type_result asg::type::Float::common (asg::type::Const const & other) const {
        return asg::common(*this)(other.type);
    }

    bool asg::type::Float::same (asg::type::Float const &) const {
        return true;
    }

    //// String ////

    std::string asg::type::String::display () const {
        return "String";
    }

    asg::common_type_result asg::type::String::common (asg::type::String const &) const {
        return {asg::type::String{}};
    }

    bool asg::type::String::same (asg::type::String const &) const {
        return true;
    }

    //// In ////

    template <>
    std::string asg::type::In::display () const {
        return "T in"; // TODO
    }

    // Note: In the following implementations, the trivial constraints `requires true` and `requires (!false)`
    // are necessary because of the original declarations `requires Complete` and `requires (!Complete)`.
    // (Complete is explicitly specified here as either true or false.)

    template <bool Complete>
    asg::decay_result asg::type::in_type<Complete>::decay () const requires Complete {
        return *type;
    }
    template asg::decay_result asg::type::in_type<true>::decay () const;

    template <bool Complete>
    bool asg::type::in_type<Complete>::same (asg::type::In const & other) const requires Complete {
        return asg::same(type, other.type);
    }
    template bool asg::type::in_type<true>::same (asg::type::In const & other) const;

    template <bool Complete>
    asg::complete_result asg::type::in_type<Complete>::complete () const requires (!Complete) {
        auto result = asg::complete(type);
        if (!result)
            return result.error();
        return {asg::type::In {
            .type = *result
        }};
    }
    template asg::complete_result asg::type::in_type<false>::complete () const;

    //// Out ////

    template <>
    std::string asg::type::Out::display () const {
        return "T out"; // TODO
    }

    template <bool Complete>
    asg::decay_result asg::type::out_type<Complete>::decay () const requires Complete {
        return *type;
    }
    template asg::decay_result asg::type::out_type<true>::decay () const;

    template <bool Complete>
    bool asg::type::out_type<Complete>::same (asg::type::Out const & other) const requires Complete {
        return asg::same(type, other.type);
    }
    template bool asg::type::out_type<true>::same (asg::type::Out const & other) const;

    template <bool Complete>
    asg::complete_result asg::type::out_type<Complete>::complete () const requires (!Complete) {
        auto result = asg::complete(type);
        if (!result)
            return result.error();
        return {asg::type::Out {
            .type = *result
        }};
    }
    template asg::complete_result asg::type::out_type<false>::complete () const;

    //// Const ////

    template <>
    std::string asg::type::Const::display () const {
        return "T const"; // TODO
    }

    template <bool Complete>
    asg::decay_result asg::type::const_type<Complete>::decay () const requires Complete {
        return *type;
    }
    template asg::decay_result asg::type::const_type<true>::decay () const;

    template <bool Complete>
    asg::common_type_result asg::type::const_type<Complete>::common (asg::type::Const const & other) const requires Complete {
        auto result = asg::common(type, other.type);
        if (!result)
            return result.error();
        return {asg::type::Const {
            .type = *result
        }};
    }
    template asg::common_type_result asg::type::const_type<true>::common (asg::type::Const const & other) const;

    template <bool Complete>
    bool asg::type::const_type<Complete>::same (asg::type::Const const & other) const requires Complete {
        return asg::same(type, other.type);
    }
    template bool asg::type::const_type<true>::same (asg::type::Const const & other) const;

    template <bool Complete>
    asg::complete_result asg::type::const_type<Complete>::complete () const requires (!Complete) {
        auto result = asg::complete(type);
        if (!result)
            return result.error();
        return {asg::type::Const {
            .type = *result
        }};
    }
    template asg::complete_result asg::type::const_type<false>::complete () const;

    //// Array ////

    template <>
    std::string asg::type::Array::display () const {
        return "T [n]"; // TODO
    }

    template <bool Complete> asg::common_type_result
    asg::type::array_type<Complete>::common (asg::type::Array const & other) const requires Complete {
        auto results = (lift::category_component{util::overload {
            [] <typename T, typename U> (T const & a, U const & b) -> std::optional<asg::type::complete> {
            //requires (std::same_as<T, U> || !std::same_as<T, asg::type::Const> && std::same_as<U, asg::type::Const>)
                if (asg::same(a, b))
                    return {a};
                return {};
            },
            [] <typename T> (asg::type::Const const & a, T const & b) -> std::optional<asg::type::complete>
            requires (!std::same_as<T, asg::type::Const>) {
                if (asg::same(a, b))
                    return {a};
                if (asg::same(a, asg::type::Const{{b}}))
                    return {asg::type::Const{{a}}};
                return {};
            },
            [] <typename T> (T const & a, asg::type::Const const & b) -> std::optional<asg::type::complete>
            requires (!std::same_as<T, asg::type::Const>) {
                if (asg::same(a, b))
                    return {a};
                if (asg::same(asg::type::Const{{a}}, b))
                    return {asg::type::Const{{a}}};
                return {};
            }
        }} (type, other.type));
        if (!results)
            return results.error();
        auto result = util::unite_optionals(*results);
        if (!result)
            return result_error{"No common type for two arrays because of mismatched elements type."};
        return {asg::type::Array {
            .type = *result,
            .size = std::min(size, other.size)
        }};

    }
    template asg::common_type_result asg::type::array_type<true>::common (asg::type::Array const & other) const;

    template <bool Complete>
    bool asg::type::array_type<Complete>::same (asg::type::Array const & other) const requires Complete {
        auto result = asg::same(type, other.type);
        if (!result)
            return false;
        return
            size == other.size &&
            util::all(*result);
    }
    template bool asg::type::array_type<true>::same (asg::type::Array const & other) const;

    template <bool Complete>
    asg::complete_result asg::type::array_type<Complete>::complete () const requires (!Complete) {
        auto type_result = util::unite_results(asg::complete(type));
        if (!type_result)
            return type_result.error();

        auto size_result = lift::category_component{util::overload {
            [] (value::unknown const &) -> result<int> {
                return result_error{"Unknown array size."};
            },
            [] <asg::interface::value Value> (Value const & value) -> result<int> {
                return asg::get<integral>(asg::convert(asg::type::Int{})(value));
            }
        }} (size);
        if (!size_result)
            return size_result.error();

        return {asg::type::Array {
            .type = *type_result,
            .size = *size_result
        }};
    }
    template asg::complete_result asg::type::array_type<false>::complete () const;

    //// Buffer ////

    template <>
    std::string asg::type::Buffer::display () const {
        return "buffer [n]"; // TODO
    }

    template <bool Complete>
    asg::common_type_result asg::type::buffer_type<Complete>::common (asg::type::Buffer const & other) const requires Complete {
        if (size != other.size)
            return result_error{"No common type for two buffers because of different sizes."};
        return {*this};
    }
    template asg::common_type_result asg::type::buffer_type<true>::common (asg::type::Buffer const & other) const;

    template <bool Complete>
    bool asg::type::buffer_type<Complete>::same (asg::type::Buffer const & other) const requires Complete {
        return size == other.size;
    }
    template bool asg::type::buffer_type<true>::same (asg::type::Buffer const & other) const;

    template <bool Complete>
    asg::complete_result asg::type::buffer_type<Complete>::complete () const requires (!Complete) {
        auto size_result = lift::category_component{util::overload {
            [] (value::unknown const &) -> result<integral> {
                return result_error{"Unknown array size."};
            },
            [] <asg::interface::value Value> (Value const & value) -> result<integral> {
                return asg::get<integral>(asg::convert(asg::type::Int{})(value));
            }
        }} (size);
        if (!size_result)
            return size_result.error();

        return {asg::type::Buffer {
            .size = *size_result
        }};
    }
    template asg::complete_result asg::type::buffer_type<false>::complete () const;

    //// Function ////

    template <>
    std::string asg::type::Function::display () const {
        return "Out (In)"; // TODO
    }

    template <bool Complete>
    asg::common_type_result asg::type::function_type<Complete>::common (asg::type::Function const & other) const requires Complete {
        auto out_result = asg::same(out, other.out);
        if (!out_result)
            return out_result.error();
        if (!util::all(*out_result))
            return result_error{"No common type for two functions because of diferent output types."};
        auto in_result = asg::same(in, other.in);
        if (!in_result)
            return in_result.error();
        if (!util::all(*in_result))
            return result_error{"No common type for two functions because of diferent input types."};
        return {*this};
    }
    template asg::common_type_result asg::type::function_type<true>::common (asg::type::Function const & other) const;

    template <bool Complete>
    bool asg::type::function_type<Complete>::same (asg::type::Function const & other) const requires Complete {
        auto out_result = asg::same(out, other.out);
        auto in_result  = asg::same(in,  other.in);
        return
            out_result && util::all(*out_result) &&
            in_result  && util::all(*in_result);
    }
    template bool asg::type::function_type<true>::same (asg::type::Function const & other) const;

    template <bool Complete>
    asg::complete_result asg::type::function_type<Complete>::complete () const requires (!Complete) {
        auto out_result = util::unite_results(asg::complete(out));
        if (!out_result)
            return out_result.error();
        auto in_result = util::unite_results(asg::complete(in));
        if (!in_result)
            return in_result.error();
        return {asg::type::Function {
            .out = *out_result,
            .in  = *in_result,
        }};
    }
    template asg::complete_result asg::type::function_type<false>::complete () const;

}
