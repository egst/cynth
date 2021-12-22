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

    /**
     *  Note: Slightly outdated info. (Old names)
     *
     *  context::C::Global is allocated once during the whole translation process.
     *  It represents a part of the final C code.
     *  It holds the global (static) declarations of types, functions and data
     *  and keeps track of a global id to avoid name collisions.
     *
     *  The context::Cynth (context/cynth.hpp) represents the allocation and scope mechanics of the Cynth language.
     *  It contains "abstract" entries for all allocations and declarations parallel to the final C code.
     *  Those entries contain a type and might contain values computed at compile time or
     *  names of corresponding C variables.  If an entry has no variable name, it's a compconst variable
     *  (marked const and value known at compile time) that needs no C declaration.
     *  User defined type aliases are also stored in this context structure and are not reflected in the final C code.
     *  All evaluation and translation operations refer to this context for any kind of name lookup.
     *  After finding an entry for the given name, either the value is used as a compilation constant or
     *  the variable name is used to form C expressions and statements.
     *  The scope is implemented by creating new contexts linked to their parent and passing them
     *  to translation and evaluation functions in nested contexts.
     *
     *  Update: (description might not fit with the rest of this docblock)
     *  context::C::Function contains function-lifetime allocations.
     *
     *  Update: (description might not fit with the rest of this docblock)
     *  context::C::Block is used to generate declarations for translation of functions.
     *  Functions are const, so they cannot be reassigned, but the fact that (expression) blocks,
     *  functions and if..else expressions might return different functions based on runtime state
     *  means, that for each such function, there must be multiple definitions in the C code
     *  for different alternatives of the function body implementation, its return types and capture types.
     *  All of this is accumulated in context::C::Block when evaluating these compound "returning" expressions
     *  and later used to create actual definitions in context::C::Global.
     *
     *  context::C ties all the above mentioned parts together.
     *  Like context::Cynth, new context::C linked to their parents are created to manage scope in the C code.
     *  All these contexts are linked to one context::C::Global context and one context::Cynth constext (which has its own hierarchy).
     *  There is no nesting of context::Cynth contexts in nested context::C contexts -
     *  they are just two parallel constructs linked to each other.
     *  context::C contains local allocations (main or any user-defined functions) and declaratons
     *  (with C scope rules - functions and blocks).
     *  The linked context::C::Global stays the same during the whole translation process.
     *  The linked context::Cynth may change to a new deeper nested (child) context or go back to its parent.
     *  Memory management of the contexts linked by reference is left to the caller.
     *  The global context and the root compilation context are only allocated once,
     *  while the nested compilation contexts should be all declared on the stack of functions handling the current
     *  operation that needs the nesting.
     */

}
