#include "sem/translation_context.hpp"

#include "result.hpp"
#include "lift2.hpp"
#include "component.hpp"
#include "sem/context.hpp"
#include "sem/interface.hpp"
#include "sem/types.hpp"
#include "util/zip.hpp"

#include <string>

#define INSPECT(val) util::inspect<decltype(val)>{};

namespace cynth::sem {

    std::size_t translation_context::next_id () {
        return id++;
    }

    /**
     *  ----decl---   --tuple--
     *  (T, U, V) a = (1, x, y)
     */
    result<void> translation_context::define (
        complete_decl             const & decl,
        tuple_vector<typed_value> const & tuple_val
    ) {
        /*
         *  compconst['a'] = {{T, 1}, {U, ?}, {V, ?}}
         *
         *  decls[] = {
         *      'cth_t_U cth_ue2_a = x;'
         *      'cth_t_V cth_ue2_a = y;'
         *  }
         */

        auto converted_result = convert(decl.type, tuple_val);
        if (!converted_result)
            return converted_result.error();
        auto converted = *converted_result;

        compconst_context.define_value(decl.name, converted);

        for (auto const & [i, type, value] : util::enumerate(decl.type, converted)) {

            if (value.value)
                continue; // Skip compconst values.

            if (!value.expression)
                return result_error{"This value cannot be translated."};

            //INSPECT(type); // complete_type

            // {transl_type(type)} cth_ue{i} = 
            // Possible C types:
            // Simple:      (`bool` | `int` | `float`)
            // ConstSimple: <Simple> `const`
            // Array:       (<Simple> | <ConstSimple> ) `*`
            // Const:       (<Simple> | <Array>) `const`
            // In:          <Simple>  # in global scope only
            // Out:         <Simple>  # in global scope only
            // Function:    `cth_c_foo_123` # named context struct passed around at runtime +
            //                              # function name inserted at compile time

            sem::transl_type(type);

            lift2<target::category>(
                [] (auto && type) {
                    
                }
            )(type);

        }

        return {};
    }

    /**
     *  -----decls-----   --tuple--
     *  ((T, U) a, V b) = (1, x, y)
     */
    result<void> translation_context::define (
        tuple_vector<complete_decl> const & decls,
        tuple_vector<typed_value>   const & tuple_val
    ) {
        auto value_begin = tuple_val.begin();

        for (auto & decl : decls) {
            if (static_cast<std::size_t>(tuple_val.end() - value_begin) < decl.type.size())
                return result_error{"Less values than types in a definition."};

            // TODO: Why don't any of these work?
            //tuple_part.assign(value_begin, value_begin + decl.type.size());
            //tuple_part.reserve(decl.type.size());
            //std::copy(value_begin, value_begin + decl.type.size(), std::back_inserter(tuple_part));
            // For now, pushing elements one by one:
            tuple_vector<typed_value> tuple_part;
            for (auto it = value_begin; it != value_begin + decl.type.size(); ++it) tuple_part.push_back(*it);

            value_begin += decl.type.size();

            define(decl, tuple_part);

            //converted ~ vector<typed_value> ~ vector<struct{complete_type, optional<complete_value>, optional<string>}>
            //decl      ~ declaration         ~ struct{string, vector<complete_type>}
            // t_T n_e1 = e;
            // t_T n_e2 = f;
            // t_T$U$V n = (t_T$U$V) {
            //     e,
            //     f,
            //     g
            // }

            // Convert to the correct type:
            // TODO: Only check the types instead
            /*
            auto conversion_results = convert(ctx)(value, decl.type);
            if (!conversion_results)
                return conversion_results.error();
            auto conversion_result = util::unite_results(*conversion_results);
            if (!conversion_result)
                return conversion_result.error();
            auto converted = *std::move(conversion_result);
            */

            // TODO
            /*
            auto define_result = ctx.define_value(decl.name, converted);
            if (!define_result)
                return define_result.error();
            */
        }

        if (value_begin != tuple_val.end())
            return result_error{"More values than types in a definition."};

        return {};
    }

    // TODO: For now, a whole tuple must be compconst to use any of its values as compconst.
    // In future versions, it would be nice to eliminate this limitation.
    result<void> translation_context::define (
        std::string                       const & name,
        tuple_vector<type::complete> const & type,
        tuple_vector<typed_value>    const & values
    ) {
        return {};
        /*
        bool compconst = true;
        for (auto && value : values) {
            if (!value.value)
                compconst = false;
            // declare arrays to keep their sizes
        }
        if (compconst)
            compconst_context.define_value(name, values);

        // TODO: results
        ctx.declare_value(name, type);
        ctx.init_value(name, value);
        */
    }

    result<void> translation_context::declare (
        std::string                       const &,
        tuple_vector<type::complete> const &
    ) {
        return {};
    }

    result<void> translation_context::assign (
        std::string               const &,
        tuple_vector<typed_value> const &
    ) {
        return {};
    }

}
