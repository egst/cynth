#pragma once

#include <cstddef>
#include <string>
#include <unordered_set>

#include "esl/component.hpp"
#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include "context/branching.hpp"
#include "context/function.hpp"
#include "context/global.hpp"
#include "context/lookup.hpp"

namespace cynth::context {

    struct Main {

        Main (
            Global    & global,
            Function  & function,
            Branching & branching
        ):  global{global},
            function{function},
            branching{branching} {}

        Main makeScopeChild     ();
        Main makeBranchingChild (Branching &);
        Main makeFunctionChild  (Function &);

        void mergeNestedChild   (Main const &) {}
        void mergeFunctionChild (Main const &) {}

        void insertStatement (std::string);

        /** Number of local statements. */
        bool count () const;

        /** Check if any local statements present. */
        bool empty () const;

        // TODO: I might limit the uniqueness of these ids to functions (or something) in the future.
        // For now, this simply counts the global incremental id.
        std::size_t nextId ();

        Global    & global;
        Function  & function;
        Branching & branching;
        Lookup      lookup;

    protected:
        // TODO: Don't forget about the indent.
        // Increase it in scope children. Reset it for function children.
        // Use it in the insert<whatever> methods.
        std::size_t indent = 0;

        std::vector<std::string> statements; // including stuff like: `if (...) {`, `for (...) {`, `{`, `}`
    };

#if 0
    struct FunctionDecl {
        friend Main;

        /***
        struct cth_ret_f  { ... }; // returnType
        struct cth_ctx_f0 { ... }; // contextTypes[0]
        struct cth_ctx_f1 { ... }; // contextTypes[1]
        ...
        struct cth_ctx_f  {        // contextType
            int branch;
            union { cth_ctx_f0 e0; cth_ctx_f1 e1; ... } data;
        };
        cth_ret_f cth_fun_f0 (cth_ctx_f0 const * ctx, ...) { ... } // functionNames[0]
        cth_ret_f cth_fun_f1 (cth_ctx_f1 const * ctx, ...) { ... } // functionNames[1]
        ...
        cth_ret_f cth_fun_f  (cth_ctx_f  const * ctx, ...) {       // functionName
            switch (ctx.branch) {
            case 0: return cth_ctx_f0(ctx.data.e0, ...);
            case 1: return cth_ctx_f1(ctx.data.e1, ...);
            ...
            }
        }
        ***/
        // single function or switch for the alternatives:
        std::optional<std::string> functionName;
        std::optional<std::string> returnType;
        std::optional<std::string> contextType;
        // runtime function alternatives:
        std::optional<std::string> functionNames;
        std::vector<std::string>   contextTypes;
    };
#endif


}
