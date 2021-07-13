#include "asg/types.hpp"

#include "asg/interface.hpp"
#include "asg/declarations.hpp"
#include "component.hpp"
#include "util/general.hpp"
#include "util/container.hpp"

#include <string>

namespace cynth {

    //// Forward declarations/instantiations ////

    // This is just crazy...
    // C++ is supposed to be an OOP language, yet the more I follow the OOP structure, the more boilerplate I need to write.
    // All of this wouldn't be necessary if common, same etc. were free functions.
    // I don't want to rewrite it all though, so for now, let's keep it the way it is.

    template <> asg::common_type_result asg::type::Const    ::common(asg::type::Const    const &) const requires true;
    template <> asg::common_type_result asg::type::Array    ::common(asg::type::Array    const &) const requires true;
    template <> asg::common_type_result asg::type::Buffer   ::common(asg::type::Buffer   const &) const requires true;
    template <> asg::common_type_result asg::type::Function ::common(asg::type::Function const &) const requires true;

    template <> bool asg::type::In       ::same(asg::type::In       const &) const requires true;
    template <> bool asg::type::Out      ::same(asg::type::Out      const &) const requires true;
    template <> bool asg::type::Const    ::same(asg::type::Const    const &) const requires true;
    template <> bool asg::type::Array    ::same(asg::type::Array    const &) const requires true;
    template <> bool asg::type::Buffer   ::same(asg::type::Buffer   const &) const requires true;
    template <> bool asg::type::Function ::same(asg::type::Function const &) const requires true;

    //// Categories ////

    template <>
    void component_deleter<asg::type::complete>::operator () (asg::type::complete * ptr) const {
        delete ptr;
    };

    template <>
    asg::type::complete * component_allocator<asg::type::complete>::operator () (asg::type::complete const & other) const {
        return new asg::type::complete{other};
    };

    template <>
    asg::type::complete * component_allocator<asg::type::complete>::operator () (asg::type::complete && other) const {
        return new asg::type::complete{std::move(other)};
    };

    template <>
    void component_deleter<asg::type::incomplete>::operator () (asg::type::incomplete * ptr) const {
        delete ptr;
    };

    template <>
    asg::type::incomplete * component_allocator<asg::type::incomplete>::operator () (asg::type::incomplete const & other) const {
        return new asg::type::incomplete{other};
    };

    template <>
    asg::type::incomplete * component_allocator<asg::type::incomplete>::operator () (asg::type::incomplete && other) const {
        return new asg::type::incomplete{std::move(other)};
    };

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

    template <>
    asg::decay_result asg::type::In::decay () const requires true {
        return *type;
    }

    template <>
    bool asg::type::In::same (asg::type::In const & other) const requires true {
        return asg::same(type, other.type);
    }

    template <>
    asg::complete_result asg::type::in_type<false>::complete () const requires (!false) {
        auto result = asg::complete(type);
        if (!result)
            return result.error();
        return {asg::type::In {
            .type = *result
        }};
    }

    //// Out ////

    template <>
    std::string asg::type::Out::display () const {
        return "T out"; // TODO
    }

    template <>
    asg::decay_result asg::type::Out::decay () const requires true {
        return *type;
    }

    template <>
    bool asg::type::Out::same (asg::type::Out const & other) const requires true {
        return asg::same(type, other.type);
    }

    template <>
    asg::complete_result asg::type::out_type<false>::complete () const requires (!false) {
        auto result = asg::complete(type);
        if (!result)
            return result.error();
        return {asg::type::Out {
            .type = *result
        }};
    }

    //// Const ////

    template <>
    std::string asg::type::Const::display () const {
        return "T const"; // TODO
    }

    template <>
    asg::decay_result asg::type::Const::decay () const requires true {
        return *type;
    }

    template <>
    asg::common_type_result asg::type::Const::common (asg::type::Const const & other) const requires true {
        auto result = asg::common(type, other.type);
        if (!result)
            return result.error();
        return {asg::type::Const {
            .type = *result
        }};
    }

    template <>
    bool asg::type::Const::same (asg::type::Const const & other) const requires true {
        return asg::same(type, other.type);
    }

    template <>
    asg::complete_result asg::type::const_type<false>::complete () const requires (!false) {
        auto result = asg::complete(type);
        if (!result)
            return result.error();
        return {asg::type::Const {
            .type = *result
        }};
    }

    //// Array ////

    template <>
    std::string asg::type::Array::display () const {
        return "T [n]"; // TODO
    }

    template <>
    asg::common_type_result asg::type::Array::common (asg::type::Array const & other) const requires true {
        auto result = asg::same(type, other.type);
        if (!result)
            return result.error();
        if (!util::all(*result))
            return error{"No common type for two arrays because of mismatched elements type."};
        if (size != other.size)
            return error{"No common type for two arrays because of different sizes."};
        return {*this};
    }

    template <>
    bool asg::type::Array::same (asg::type::Array const & other) const requires true {
        auto result = asg::same(type, other.type);
        if (!result)
            return false;
        return
            size == other.size &&
            util::all(*result);
    }

    template <>
    asg::complete_result asg::type::array_type<false>::complete () const requires (!false) {
        auto type_result = util::unite_results(asg::complete(type));
        if (!type_result)
            return type_result.error();

        auto size_result = lift::category_component{util::overload {
            [] (value::unknown const &) -> result<int> {
                return error{"Unknown array size."};
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

    //// Buffer ////

    template <>
    std::string asg::type::Buffer::display () const {
        return "buffer [n]"; // TODO
    }

    template <>
    asg::common_type_result asg::type::Buffer::common (asg::type::Buffer const & other) const requires true {
        if (size != other.size)
            return error{"No common type for two buffers because of different sizes."};
        return {*this};
    }

    template <>
    bool asg::type::Buffer::same (asg::type::Buffer const & other) const requires true {
        return size == other.size;
    }

    template <>
    asg::complete_result asg::type::buffer_type<false>::complete () const requires (!false) {
        auto size_result = lift::category_component{util::overload {
            [] (value::unknown const &) -> result<integral> {
                return error{"Unknown array size."};
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

    //// Function ////

    template <>
    std::string asg::type::Function::display () const {
        return "Out (In)"; // TODO
    }

    template <>
    asg::common_type_result asg::type::Function::common (asg::type::Function const & other) const requires true {
        auto out_result = asg::same(out, other.out);
        if (!out_result)
            return out_result.error();
        if (!util::all(*out_result))
            return error{"No common type for two functions because of diferent output types."};
        auto in_result = asg::same(in, other.in);
        if (!in_result)
            return in_result.error();
        if (!util::all(*in_result))
            return error{"No common type for two functions because of diferent input types."};
        return {*this};
    }

    template <>
    bool asg::type::Function::same (asg::type::Function const & other) const requires true {
        auto out_result = asg::same(out, other.out);
        auto in_result  = asg::same(in,  other.in);
        return
            out_result && util::all(*out_result) &&
            in_result  && util::all(*in_result);
    }

    template <>
    asg::complete_result asg::type::function_type<false>::complete () const requires (!false) {
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

}
