#include "sem/translation_context.hpp"

#include <string>
#include <utility>

#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/tiny_vector.hpp"

#include "sem/context_types.hpp"
#include "sem/declarations.hpp"
#include "sem/interface.hpp"
#include "sem/translation.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth::sem {

    std::size_t TranslationContext::nextId () {
        return id++;
    }

    /*
        Notes on the translation process:

        BASIC CASE:
        only variables in function scope will be declared in C code
        if a variable's value is known at compile time and it is const, it will not be declared in C code
        `(Int, Int const) x = (1, 2)` will only result in a `cth_int v1_{id}_x = 1;` declaration
        since the first value of the tuple might be assigned a runtime value
        the same declaration outside of any function scope will result in no c declaration
        since there is no way to assign a runtime value to it
        also note, that even some functions will be evaluated during compilation
        and their locally declared variables will not be declared in C code

        IO:
        the runtime-only values - in, out and buffers:
        these may only be declared and defined outside of any function scope
        (assignment is impossible (they are implicitly const) except for value-assignment `outVar[] = val` for out types)
        a global C declaration will hold an underlying value while the "pointer" value is known at compile time
        and will be inserted directly into C code as the name of the global variable
        `Int out a; Int out b = a` will result in a single global `cth_int cth_uo_{id}_a = 0;` declaration
        mutable at run-time while the `cth_uo_{id}_a` name will be stored only during compilation
        as a compconst value of the variable
        `b[] = val` will be translated to simply `cth_uo_{id}_a = {translate(val)};`
        while `fun(b, x, y)` will be translated to something like
        `cth_uf_{fid}_fun(&cth_uc_{fid}_fun, cth_v1_{xid}_x, cth_v2_{xid}_x, cth_v1_{yid}_y)`
        the same goes for the in types
        buffers will have more complex global declarations but the general idea is the same as well

        STATIC:
        static variables have the same semantics as in variables except that there is no volatility
        they also are implicitly const and can only be declared outside of any function scope.

        FUNCTIONS:
        functions are implicitly const too, but their values might be dependant on runtime values.
        a function might capture runtime values (always by value)
        e.g. `buffer [n] b = Int fn (Int time) { Int helper (Int x) x + time; return helper(5) }`
        or it might be initialized to a conditionally selected function
        e.g. `if (val) Int fn (Int x) x + 1 else Int fn (Int x) x + 2`
        or `makeFun(val)` which has multiple return branches
        the first runtime dependancy is handled by passing an implicit parameter with the captured context
        the second runtime dependancy is handled by creating a helper "switch" function that
        will delegate to a specific version of the function depending on a runtime value (passed in the context)
        `Int (Int) fun = if (val) Int fn (Int x) x + 1 else Int fn (Int x) x + a`
        with a runtime `Int a` value will be translated to:
        ```
        struct cth_c_{id0}_fun {
            int branch;
            cth_int v1_a;
        };
        cth_int cth_f0_{id1}_fun (struct cth_c_{id0}_fun const * ctx, cth_int v1_{id2}_x) {
            return cth_add$int(v1_{id2}_x, 1);
        }
        cth_int cth_f1_{id1}_fun (struct cth_c_{id0}_fun const * ctx, cth_int v1_{id3}_x) {
            return cth_add$int(v1_{id2}_x, ctx->v1_a);
        }
        cth_int cth_f_{id1}_fun (struct cth_c_{id0}_fun const * ctx, cth_int v1_{id4}_x) {
            switch (ctx->branch) {
            case 0:
                return cth_f0_{id1}_fun(ctx, v1_{id4}_x);
            case 1:
                return cth_f1_{id1}_fun(ctx, v1_{id4}_x);
            }
        }
        ```

        ARRAYS:
        for every array, a pointer and possibly an implicit underlying value is declared
        `Int [3] a = [1, 2, 3]` will result in:
        `cth_int cth_av_{id} [3] = {1, 2, 3};` and `cth_int * v1_{id}_a = &cth_av_{id};`
        `(Int const [3], Int [3] const) b = (a, a)` will result in:
        `cth_int const * v1_{id1}_b = v1_{id}_a; cth_int * const v2_{id2}_b = v1_{id}_a;`
        capturing arrays should be implemented with a compile-time copy-on-write allocation
        (a new array is allocated if an assignment might happen in any of the branches)
        and maybe run-time conditional copy (a new array is allocated based on a compile-time decision,
        but the values are only copied based on a run-time decision - when the assignment is actually about to happen)
        however, to simplify the initial implementation, (in runtime (*)) arrays will be captured by a constant reference

        ```
        Int (Int) fun () {
            Int [3] a = [1, 2, 3];
            return Int fn (Int x) {
                return a[x];
            }
        }
        ```
        ```
        struct cth_c_{...}_fun {};
        struct cth_c_{...} {
            struct cth_arr$int$3 v1_a;
        };
        struct cth_c_{...} cth_f_fun (struct cth_c_{...}_fun const *) {
            cth_arr$int$3 av_{...} = {{1, 2, 3}};
            cth_int * v1_{...}_a = av_{...}.value;
            return (struct cth_c_{...}) {
                .v1_a = cth_arr_copy$int$3(v1_{...}_a)
            };
        }
        int main () {
            cth_c_{...}_fun v1_{...}_fun = {};
        }
        ```

        ```
        Int [3] a = [1, 2, 3];
        Int (Int) fun (Int v) {
            a[1] = v;
            return Int fn (Int x) {
                return a[x];
            }
        }
        ```
        ```
        struct cth_c_{...}_fun {
            cth_arr$int$3 v1_a;
        };
        struct cth_c_{...} {
            struct cth_arr$int$3 v1_a;
        };
        struct cth_c_{...} cth_f_fun (struct cth_c_{...}_fun const * ctx, cth_int v1_{...}_v) {
            ctx->v1_a.value[1] = v1_{...}_v;
            return (struct cth_c_{...}) {
                .v1_a = cth_arr_copy$int$3(v1_{...}_a)
            };
        }
        int main () {
            cth_arr$int$3 av_{...} = {{1, 2, 3}};
            int * v1_{...}_a = av_{...}.value;
            cth_c_{...}_fun v1_{...}_fun = {
                .v1_a = cth_arr_copy$int$3(v1_{...}_a.value)
            };
        }
        ```

        Possible C types:
        Simple:      (`bool` | `int` | `float`)
        ConstSimple: <Simple> `const`
        Array:       (<Simple> | <ConstSimple> ) `*`
        Const:       (<Simple> | <Array>) `const`
        In:          <Simple>  # in global scope only
        Out:         <Simple>  # in global scope only
        Function:    `cth_c_foo_123 const` # named context struct passed around at runtime +
                                           # function name inserted at compile time
        Buffer:      `float *`             # maybe const?

        Prefixes:
        in, out, buffer and static values are declared globally and thus get the `cth_` prefix

        IN BASIC:
        global:
            cth_{type} volatile cth_val_{i = nextId()};
         local:
            cth_{type} const * var_{nextId()} = &cth_val_{i};

        OUT BASIC:
        global:
            cth_{type} cth_out_{i = nextId()};
        local:
            cth_{type} * var_{nextId()} = &cth_val_{i};

        BUFFER:
        common:
            struct cth_buff${size} {
                cth_float data [{size}];
                cth_int offset;
            };
        global:
            struct cth_buff${size} cth_val_{i = nextId()};
        local:
            struct cth_buff${size} * var_{nextId()} = &cth_val_{i};

        BASIC:
        local:
            cth_{type} var_{nextId()} = 0;

        STATIC BASIC:
        global:
            cth_{type} const cth_val_{i = nextId()};
        local:
            cth_{type} const * var_{nextId()} = &cth_val_{i};

        CONST BASIC:
        local:
            cth_{type} const var_{nextId()} = 0;

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
        function scope:
            cth_arr${size}${type1}${type2}$... val_{i = nextId()};
        local:
            cth_tup${type1}${type2}$... * var_{j = nextId()} = val_{i}.value;
            cth_tup${type1}${type2}$... * const var_{j = nextId()} = val_{i}.value; // const
            arr_copy_to({definitino}, var_{j})

        STATIC ARRAY:
        global:
            cth_arr${size}${type1}${type2}$... const cth_val_{i = nextId()}; // implicitly const
        local:
            cth_tup${type1}${type2}$... const * const var_{j = nextId()} = cth_val_{i}.value; // implicitly const & const-valued
            arr_copy_to({definitino}, var_{j});

        FUNCTIION:
        global:
        struct cth_ret_{i = nextId()} {
            {retType1} e1;
            {retType2} e2;
            ...
        };
        struct cth_ctx_{i} {
            int branch;
            {capType1} val_{capName1}; // TODO: name or id?
            {capType2} val_{capName2};
            ...
        };
        cth_ret_{i} cth_fun0_{i} (
            cth_ctx_{i} const * ctx,
            cth_{argType1} val_{j = nextId()},
            cth_{argType2} val_{k = nextId()},
            ...
        ) { ... }
        cth_ret_{i} cth_fun1_{i} (
            cth_ctx_{i} const * ctx,
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
                return cth_fun0_{i}(ctx, val_{j}, val_{k}, ...);
            case 1:
                return cth_fun1_{i}(ctx, val_{j}, val_{k}, ...);
            ...
            }
        }

     */

    /**
     *  ----decl---   --tuple--
     *  (T, U, V) a = (1, x, y)
     */
    esl::result<void> TranslationContext::define (
        CompleteDeclaration          const & decl,
        esl::tiny_vector<TypedValue> const & tuple
    ) {
        auto convertedResult = convert(decl.type, tuple);
        if (!convertedResult)
            return convertedResult.error();
        auto converted = *convertedResult;

        // compilation definition:
        compconst.defineValue(decl.name, converted);

        // runtime definition:
        for (auto const & [i, type, value] : esl::enumerate(decl.type, converted)) {
            if (!value.expression)
                return esl::result_error{"This value cannot be translated."}; // TODO: Maybe for some types it's ok?
            auto definition = *value.expression;
            auto compval = value.value.has_value();
            auto translationResult = esl::lift<esl::target::category>(
                translateDefinition(*this, definition, compval)
            )(type);
            if (!translationResult)
                return translationResult.error();
        }

        return {};
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
