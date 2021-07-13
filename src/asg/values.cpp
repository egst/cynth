#include "asg/values.hpp"

#include "config.hpp"
#include "component.hpp"
#include "ast/categories/array_elem.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "asg/interface.hpp"
#include "asg/types.hpp"
#include "util/operations.hpp"
#include "util/string.hpp"

#include <iostream>
#include <utility>

namespace cynth {

    //// Implementation helpers ////

    asg::conversion_result make_const (auto const & result) {
        if (!result)
            return result.error();
        return {asg::value::Const {
            .value = *result
        }};
    }

    //// Categories ////

    template <>
    void component_deleter<asg::value::complete>::operator () (asg::value::complete * ptr) const {
        delete ptr;
    };

    template <>
    asg::value::complete * component_allocator<asg::value::complete>::operator () (asg::value::complete const & other) const {
        return new asg::value::complete{other};
    };

    template <>
    asg::value::complete * component_allocator<asg::value::complete>::operator () (asg::value::complete && other) const {
        return new asg::value::complete{std::move(other)};
    };

    template <>
    void component_deleter<asg::value::incomplete>::operator () (asg::value::incomplete * ptr) const {
        delete ptr;
    };

    template <>
    asg::value::incomplete * component_allocator<asg::value::incomplete>::operator () (asg::value::incomplete const & other) const {
        return new asg::value::incomplete{other};
    };

    template <>
    asg::value::incomplete * component_allocator<asg::value::incomplete>::operator () (asg::value::incomplete && other) const {
        return new asg::value::incomplete{std::move(other)};
    };

    //// Bool ////

    std::string asg::value::Bool::display () const {
        return "Bool(" + std::string{value ? "true" : "false"} + ")";
    }

    asg::get_result<bool> asg::value::Bool::get () const {
        return value;
    }

    asg::conversion_result asg::value::Bool::convert (asg::type::Bool const &) const {
        return {*this};
    }

    asg::conversion_result asg::value::Bool::convert (asg::type::Int const &) const {
        return asg::value::make_int(util::btoi(value));
    }

    asg::conversion_result asg::value::Bool::convert (asg::type::Float const &) const {
        return asg::value::make_float(util::btof(value));
    }

    asg::conversion_result asg::value::Bool::convert (asg::type::Const const & to) const {
        return make_const(asg::convert_to(*this)(to.type));
    }

    asg::value_type_result asg::value::Bool::value_type () const {
        return asg::type::Bool{};
    }

    //// Int ////

    std::string asg::value::Int::display () const {
        return "Int(" + std::to_string(value) + ")";
    }

    asg::get_result<integral> asg::value::Int::get () const {
        return value;
    }

    asg::conversion_result asg::value::Int::convert (asg::type::Bool const &) const {
        return asg::value::make_bool(util::itob(value));
    }

    asg::conversion_result asg::value::Int::convert (asg::type::Int const &) const {
        return {*this};
    }

    asg::conversion_result asg::value::Int::convert (asg::type::Float const &) const {
        return asg::value::make_float(util::itof(value));
    }

    asg::conversion_result asg::value::Int::convert (asg::type::Const const & to) const {
        return make_const(asg::convert_to(*this)(to.type));
    }

    asg::value_type_result asg::value::Int::value_type () const {
        return asg::type::Int{};
    }

    //// Float ////

    std::string asg::value::Float::display () const {
        return "Float(" + std::to_string(value) + ")";
    }

    asg::get_result<floating> asg::value::Float::get () const {
        return value;
    }

    asg::conversion_result asg::value::Float::convert (asg::type::Bool const &) const {
        return asg::value::make_bool(util::ftob(value));
    }

    asg::conversion_result asg::value::Float::convert (asg::type::Int const &) const {
        return asg::value::make_int(util::ftoi(value));
    }

    asg::conversion_result asg::value::Float::convert (asg::type::Float const &) const {
        return {*this};
    }

    asg::conversion_result asg::value::Float::convert (asg::type::Const const & to) const {
        return make_const(asg::convert_to(*this)(to.type));
    }

    asg::value_type_result asg::value::Float::value_type () const {
        return asg::type::Float{};
    }

    //// String ////

    std::string asg::value::String::display () const {
        return "String(" + value + ")";
    }

    asg::get_result<string> asg::value::String::get () const {
        return error{"Strings are not supported yet."};
    }

    asg::value_type_result asg::value::String::value_type () const {
        return asg::type::String{};
    }

    //// In ////

    std::string asg::value::In::display () const {
        return "in(" + asg::display(*value) + ")";
    }

    asg::conversion_result asg::value::In::convert (asg::type::Bool const & to) const {
        return asg::convert(to)(value);
    }

    asg::conversion_result asg::value::In::convert (asg::type::Int const & to) const {
        return asg::convert(to)(value);
    }

    asg::conversion_result asg::value::In::convert (asg::type::Float const & to) const {
        return asg::convert(to)(value);
    }

    asg::conversion_result asg::value::In::convert (asg::type::In const &) const {
        return error{"In to in type conversion is not supported yet."};
    }

    asg::conversion_result asg::value::In::convert (asg::type::Const const & to) const {
        return make_const(asg::convert(value, to.type));
    }

    asg::value_type_result asg::value::In::value_type () const {
        return asg::type::In {
            .type = asg::value_type(value)
        };
    }

    //// Out ////

    std::string asg::value::Out::display () const {
        return "out(" + asg::display(*value) + ")";
    }

    asg::conversion_result asg::value::Out::convert (asg::type::Out const &) const {
        return error{"Out to out type conversion is not supported yet."};
    }

    asg::value_type_result asg::value::Out::value_type () const {
        return asg::type::Out {
            .type = asg::value_type(value)
        };
    }

    //// Const ////

    std::string asg::value::Const::display () const {
        return "const(" + asg::display(*value) + ")";
    }

    asg::conversion_result asg::value::Const::convert (asg::type::Bool const & to) const {
        return asg::convert(to)(value);
    }

    asg::conversion_result asg::value::Const::convert (asg::type::Int const & to) const {
        return asg::convert(to)(value);
    }

    asg::conversion_result asg::value::Const::convert (asg::type::Float const & to) const {
        return asg::convert(to)(value);
    }

    asg::conversion_result asg::value::Const::convert (asg::type::Const const & to) const {
        return make_const(asg::convert(value, to.type));
    }

    asg::conversion_result asg::value::Const::convert (asg::type::Function const & to) const {
        return asg::convert(to)(value);
    }

    asg::value_type_result asg::value::Const::value_type () const {
        return asg::type::Const {
            .type = asg::value_type(value)
        };
    }

    //// Array ////

    std::string asg::value::Array::display () const {
        return
            "array<" +
            asg::display_tuple(type) +
            ">(" +
            util::parenthesized(util::join(", ", lift::component{asg::display_tuple}(value))) +
            ")";
    }

    asg::conversion_result asg::value::Array::convert (asg::type::Array const & to) const {
        if (asg::same(to)(value_type()))
            return {*this};
        return error{"Invalid array conversion."};
    }

    asg::conversion_result asg::value::Array::convert (asg::type::Const const & to) const {
        return make_const(asg::convert_to(*this)(to.type));
    }

    asg::value_type_result asg::value::Array::value_type () const {
        return asg::type::Array {
            .type = type,
            .size = static_cast<integral>(value.size()) // TODO: Some safety checks or enforce an invariant?
        };
    }

    //// Buffer ////

    std::string asg::value::Buffer::display () const {
        return "buffer(...)";
    }

    asg::conversion_result asg::value::Buffer::convert (asg::type::Buffer const &) const {
        return error{"Array type conversions are not supported yet."};
    }

    asg::value_type_result asg::value::Buffer::value_type () const {
        return asg::type::Buffer {
            .size = static_cast<integral>(value.size()) // TODO: Some safety checks or enforce an invariant?
        };
    }

    //// Function ////

    asg::get_result<asg::value::Function> asg::value::Function::get () const {
        return *this;
    }

    std::string asg::value::Function::display () const {
        return "function(...)";
    }

    asg::conversion_result asg::value::Function::convert (asg::type::Function const & to) const {
        if (asg::same(to)(value_type()))
            return {*this};
        return error{"Invalid function conversion."};
    }

    asg::conversion_result asg::value::Function::convert (asg::type::Buffer const &) const {
        // TODO
        return error{"Function to buffer conversion is not implemented yet."};
    }

    asg::value_type_result asg::value::Function::value_type () const {
        return asg::type::Function {
            .out = out_type,
            .in  = asg::decl_type(parameters)
        };
    }

}