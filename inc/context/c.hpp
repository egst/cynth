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

        struct Global {
            std::size_t nextId ();

        protected:
            std::vector<std::string> internalTypes;
            std::vector<std::string> internalFunctions;
            std::vector<std::string> userFunctions;
            std::vector<std::string> staticData; // static lifetime allocations

            std::size_t id = 0;
        };

        C (
            C::Global      & global,
            context::Cynth & comp
        ):  globalCtx{global},
            compCtx{&comp} {}

        C makeScopeChild    ();
        C makeFunctionChild ();

        // TODO: Don't forget that these must completely ignore empty strings.
        // Update: I don't think it's needed anywhere anymore, but it still could be useful.
        // TODO: Do these really need to return a result? There's nothing exprected to go wrong.
        // Change to void and modify all calling code accordingly.
        esl::result<void> insertStatement          (std::string);
        esl::result<void> insertFunctionAllocation (std::string);
        esl::result<void> insertStaticAllocation   (std::string);
        esl::result<void> insertInternalFunction   (std::string);
        esl::result<void> insertInternalType       (std::string);

        std::size_t nextId ();

        // TODO: Make these protected and provide referential accessors for unified interface.
        Cynth     * compCtx;
        C::Global & globalCtx;

    protected:
        struct {
            std::vector<std::string> functionData; // function scope lifetime allocations
            std::vector<std::string> statements;   // including stuff like: `if (...) {`, `for (...) {`, `{`, `}`
        } local;
    };

}
