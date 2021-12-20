#pragma once

#include <cstddef>
#include <string>

#include "esl/component.hpp"
#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include "context/cynth.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"

namespace cynth::context {

    /**
     *  context::C::Global is allocated once during the whole translation process.
     *  It represents a part of the final C code.
     *  It holds the global (static) declarations of types, functions and data
     *  and keeps track of a global id to avoid name collisions.
     *
     *  The context::Cynth (context/cynth.hpp) represents the allocation and scope mechanics of the Cynth language.
     *  It contains "abstract" entries for all allocations and declarations parallel to the final C code.
     *  Those entries contain a type and might contain values computed at compile time and/or
     *  names of corresponding C variables. If an entry has no variable name, it's either not possible to translate
     *  directly (although right now there are no such constructs in Cynth) or it's a compconst value
     *  (marked const and known at compile time) that needs no C declaration or it's just not been declared
     *  by the current algorithm. (This means that the insertion of an entry and assignment of its variable name
     *  is not an atomic operation. This should probably be fixed later.)
     *  User defined type aliases are also stored in this context structure and are not reflected in the final C code.
     *  All evaluation and translation operations refer to this context for any kind of name lookup.
     *  After finding an entry for the given name, either the value is used as a compilation constant or
     *  the variable name is used to form a C expressions and statements.
     *  The scope is implemented by creating new contexts linked to their parent and passing them
     *  to translation and evaluation functions in nested contexts.
     *
     *  context::C ties the previous two together.
     *  Like context::Cynth, new context::C linked to their parents are created to manage scope in the C code.
     *  All these contexts are linked to one context::C::Global context and one context::Cynth constext (which has its own hierarchy).
     *  There is no nesting of context::Cynth contexts in nested context::C contexts - they are just two parallel constructs linked to each other.
     *  context::C contains local allocations (main or any user-defined functions) and declaratons
     *  (with C scope rules - functions and blocks).
     *  The linked context::C::Global stays the same during the whole translation process.
     *  The linked context::Cynth may change to a new deeper nested (child) context or go back to its parent.
     *  Memory management of the linked context is left to the caller.
     *  The global context and the root compilation context are only allocated once,
     *  while the nested compilation contexts should be all declared on the stack of functions handling the current
     *  operation that needs the nesting.
     */
    struct C {

        // TODO: Global could contain warning and error entries.
        // Currently the whole translation process stops at any error.
        // Maybe I should continue and just accumulate the errors (and warnings)
        // here, in the context structure.
        // Should I incorporate warnings into esl::result?
        // Or should I just insert results directly into the context structure?

        struct Global {
            std::size_t nextId ();

            void insertAllocation       (std::string);
            void insertInternalFunction (std::string);
            void insertInternalType     (std::string);

        protected:
            std::vector<std::string> internalTypes;
            std::vector<std::string> internalFunctions;
            std::vector<std::string> userFunctions;
            std::vector<std::string> data; // static lifetime allocations

            std::size_t id = 0;
        };

        struct Function {
            void insertAllocation (std::string);

        protected:
            std::vector<std::string> data; // function lifetime allocations

            std::size_t id = 0;
        };

        C (
            Global      & global,
            Function    & function,
            context::Cynth & comp
        ):  globalCtx{global},
            functionCtx{function},
            compCtx{&comp} {}

        C makeScopeChild    ();
        C makeFunctionChild ();

        void mergeScopeChild    (C const &) {}
        void mergeFunctionChild (C const &) {}

        void insertStatement (std::string);

        /** Number of local statements. */
        bool count () const;

        /** Check if any local statements present. */
        bool empty () const;

        // TODO: I might limit the uniqueness of these ids to functions (or something) in the future.
        // For now, this simply counts the global incremental id.
        std::size_t nextId ();

        Global   & global   () { return globalCtx; }
        Function & function () { return functionCtx; }
        Cynth    & comptime () { return *compCtx; }

    protected:
        Global   & globalCtx;
        Function & functionCtx;
        Cynth    * compCtx;

        // TODO: Don't forget about the indent.
        // Increase it in scope children. Reset it for function children.
        // Use it in the insert<whatever> methods.
        std::size_t indent = 0;

        std::vector<std::string> statements; // including stuff like: `if (...) {`, `for (...) {`, `{`, `}`
    };

}
