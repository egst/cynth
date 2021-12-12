#include "context/c.hpp"

#include <optional>
#include <string>
#include <utility>

#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/tiny_vector.hpp"

#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/translation.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth::context {

    std::size_t C::Global::nextId () {
        return id++;
    }

    std::size_t C::nextId () {
        return globalCtx.nextId();
    }

    esl::result<void> C::define (
        sem::CompleteDeclaration             const & decl,
        esl::tiny_vector<sem::ResolvedValue> const & tuple
    ) {
        return esl::result_error{"TODO"};
#if 0
        /*auto convertedResult = convert(*this)(decl.type, tuple);
        if (!convertedResult)
            return convertedResult.error();
        auto converted = *convertedResult;*/
        auto converted = tuple;

        // compilation definition: (this performs all the necessary type checks)
        auto compDefResult = compCtx.defineValue(decl.name, converted);
        if (!compDefResult)
            return compDefResult.error();
        auto compDefinition = *compDefResult;

        // runtime definition: (this assumes type correctness)
        for (auto const & [type, value] : esl::zip(decl.type, converted)) {
            auto expressionResult = value.getExpression(*this);
            if (!expressionResult)
                return expressionResult.error();

            auto definition = *expressionResult;
            auto compval = value.value.has_value();
            auto declarationResult = esl::lift<esl::target::category>(
                translateDefinition(*this, definition, compval)
            )(type);
            if (!declarationResult)
                return declarationResult.error();
            auto variableName = *declarationResult;
            // TODO: Store this variable name in the comCtx somewhere...
        }

        return {};
#endif
    }

// TODO
#if 0

    /**
     *  -----decls-----   --tuple--
     *  ((T, U) a, V b) = (1, x, y)
     */
    result<void> translation_context::define (
        tuple_vector<complete_decl> const & decls,
        tuple_vector<typed_value>   const & tuple
    ) {
        auto value_begin = tuple.begin();

        for (auto & decl : decls) {
            if (static_cast<std::size_t>(tuple.end() - value_begin) < decl.type.size())
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

        if (value_begin != tuple.end())
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

#endif
}

/*
    Notes on the translation process:

    BUFFER:
    common:
        struct cth_buff${size} {
            cth_float data [{size}];
            cth_int offset;
        };

    ARRAY:
    common:
        struct cth_tup${type1}${type2}$... { // for tuples of simple types only
            cth_{type1} e1;
            cth_{type2} e2;
            ...
        };
        struct cth_arr${size}${type1}${type2}$... {
            cth_tup${type1}${type2}$... data [{size}];
        };
        inline cth_arr${size}${type1}${type2}$...
        cth_arr_copy${size}${type1}${type2} (cth_tup${type1}${type2}$... const * src) {
            cth_arr${size}${type1}${type2}$... result;
            memcpy(result.data, src, {size} * sizeof(cth_tup${type1}${type2}$...));
        }

    FUNCTION:
    global:
    struct cth_ret_{i = nextId()} {
        {retType1} e1;
        {retType2} e2;
        ...
    };
    struct cth_ctx0_{i} {
        // TODO: name or id?
        {captType1} var_{captName1};
        {captType2} var_{captName2};
        ...
        // when allocations needed:
        {captValType2} val_{captName2};
        ...
    };
    struct cth_ctx1_{i} {
        {captType1} val_{captName1};
        {captType2} val_{captName2};
        ...
    };
    ...
    struct cth_ctx_{i} {
        int branch;
        union {
            cth_ctx0_{i} v0,
            cth_ctx1_{i} v1,
            ...
        } data;
    };
    cth_ret_{i} cth_fun0_{i} (
        cth_ctx0_{i} const * ctx,
        cth_{argType1} val_{j = nextId()},
        cth_{argType2} val_{k = nextId()},
        ...
    ) { ... }
    cth_ret_{i} cth_fun1_{i} (
        cth_ctx1_{i} const * ctx,
        cth_{argType1} val_{j = nextId()},
        cth_{argType2} val_{k = nextId()},
        ...
    ) { ... }
    ...
    cth_ret_{i} cth_funsw_{i} (
        cth_ctx_{i} const * ctx,
        cth_{argType1} val_{j = nextId()},
        cth_{argType2} val_{k = nextId()},
        ...
    ) {
        switch (ctx->branch) {
        case 0:
            return cth_fun0_{i}(ctx.data.v0, val_{j}, val_{k}, ...);
        case 1:
            return cth_fun1_{i}(ctx.data.v1, val_{j}, val_{k}, ...);
        ...
        }
    }

 */
