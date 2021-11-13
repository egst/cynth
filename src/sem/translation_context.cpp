#include "sem/translation_context.hpp"

#include "result.hpp"
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

    result<void> translation_context::define (
        complete_decl             const & decl,
        tuple_vector<typed_value> const & tuple
    ) {
        auto converted_result = convert(decl.type, tuple);
        if (!converted_result)
            return converted_result.error();
        auto converted = *converted_result;

        compconst_context.define_value(decl.name, converted);

        for (auto const & [type, value] : util::zip{decl.type, converted}) {

            if (value.value)
                continue; // Skip compconst values.

            if (!value.expression)
                return result_error{"This value cannot be translated."};

            //INSPECT(type);

            // cynth_t_{type} = 

        }

        return {};
    }

    result<void> translation_context::define (
        tuple_vector<complete_decl> const & decls,
        tuple_vector<typed_value>   const & values
    ) {
        auto value_begin = values.begin();

        for (auto & decl : decls) {
            if (static_cast<std::size_t>(values.end() - value_begin) < decl.type.size())
                return result_error{"Less values than types in a definition."};

            // TODO: Why don't any of these work?
            //tuple.assign(value_begin, value_begin + decl.type.size());
            //tuple.reserve(decl.type.size());
            //std::copy(value_begin, value_begin + decl.type.size(), std::back_inserter(tuple));
            // For now, pushing elements one by one:
            tuple_vector<typed_value> tuple;
            for (auto it = value_begin; it != value_begin + decl.type.size(); ++it) tuple.push_back(*it);

            value_begin += decl.type.size();

            define(decl, tuple);

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

        if (value_begin != values.end())
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
