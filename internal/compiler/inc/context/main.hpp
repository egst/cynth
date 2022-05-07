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
#include "sem/compound.hpp"

namespace cynth::context {

    struct Main {
        friend syn::node::Block;

        Global    & global;
        Function  & function;
        Branching & branching;
        Lookup      lookup;

        inline Main (
            Global    & global,
            Function  & function,
            Branching & branching
        ):  global{global},
            function{function},
            branching{branching} {}

        inline Main makeScopeChild () {
            return {global, function, branching, lookup.makeChild(), ++indent};
        }

        inline Main makeBranchingChild (Branching & branching) {
            return {global, function, branching, lookup.makeChild(), ++indent};
        }

        Main makeFunctionChild (Function & function) {
            return {global, function, branching, lookup.makeChild(), 0};
        }

        /* Note: mergeFunctionChild probably won't be neded.
        void mergeNestedChild   (Main const &); // Perform this after makeScopeChild and makeBranchingChild
        void mergeFunctionChild (Main const &); // Perform this after makeFunctionChild
        */

        void mergeChild (Main const &);

        /** Insert a local statement. */
        void insertStatement (std::string const &);

        inline std::vector<std::string> const & getStatements () { return statements; }

        /** Number of local statements. */
        inline bool count () const {
            return statements.size();
        }

        /** Check if any local statements present. */
        inline bool empty () const {
            return statements.empty();
        }

        // TODO: I might limit the uniqueness of these ids to functions (or something) in the future.
        // For now, this simply counts the global incremental id.
        inline std::size_t nextId () {
            return global.nextId();
        }

        /** Define a function based on its metadata. */
        esl::result<Global::FunctionId> defineFunction (sem::FunctionDefinition &);
        // TODO: Don't forget to set the newly generated name in the passed function's definition.

        /** Assembles the final C program. */
        std::string assemble () const;

    protected:
        // TODO: Don't forget about the indent.
        // Increase it in scope children. Reset it for function children.
        // Use it in the insert<whatever> methods.
        std::size_t indent = 0;

        std::vector<std::string> statements; // including stuff like: `if (...) {`, `for (...) {`, `{`, `}`

        inline Main (
            Global    &  global,
            Function  &  function,
            Branching &  branching,
            Lookup    && lookup,
            std::size_t  indent
        ):  global{global},
            function{function},
            branching{branching},
            lookup{std::move(lookup)},
            indent{indent} {}
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
