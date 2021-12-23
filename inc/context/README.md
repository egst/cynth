# Context

Global state of the compilation is held in these context structures.
`context::Main` is the main context structure, that is passed around during the compilation process
as a non-const reference. Compilation functions might alter the inner state of this context
and make decisions based on this state. Child contexts from can be created from `context::Main` to handle scope
(to translate nested C blocks or global C functions or just execute/evaluate nested Cynth blocks at compile-time).
`context::Main` either directly contains or just references other more specific context structures.
`context::Global` is created once at the begining of compilation and it handles global state,
like global (static) allocations and global function definitions.
`context::Function` is created once for every function and handles function-level (automatic) allocations.
`context::Branching` is created once for every block expression to keep track of possibly returned functions
to allow the processing of the `return` statement translate the function into a correct branch number
to later select the right function at runtime.
`context::Lookup` is created for every scope creating construct in Cynth
and handles lookup of values and types by their original Cynth names.
`context::Lookup` is directly contained in `context::Main` and a child `context::Lookup` is created
implicitly for a requested child of `context::Main`. Other context structures are only referenced by `context::Main`
and remain the same when creating children of `context::Main` unless explicitly created and passed
to one of the more specific child creation functions of `context::Main` by non-const reference.

Outdated info (TODO):

> context::C::Global is allocated once during the whole translation process.
> It represents a part of the final C code.
> It holds the global (static) declarations of types, functions and data
> and keeps track of a global id to avoid name collisions.
>
> The context::Cynth (context/cynth.hpp) represents the allocation and scope mechanics of the Cynth language.
> It contains "abstract" entries for all allocations and declarations parallel to the final C code.
> Those entries contain a type and might contain values computed at compile time or
> names of corresponding C variables.  If an entry has no variable name, it's a compconst variable
> (marked const and value known at compile time) that needs no C declaration.
> User defined type aliases are also stored in this context structure and are not reflected in the final C code.
> All evaluation and translation operations refer to this context for any kind of name lookup.
> After finding an entry for the given name, either the value is used as a compilation constant or
> the variable name is used to form C expressions and statements.
> The scope is implemented by creating new contexts linked to their parent and passing them
> to translation and evaluation functions in nested contexts.
>
> Update: (description might not fit with the rest of this docblock)
> context::C::Function contains function-lifetime allocations.
>
> Update: (description might not fit with the rest of this docblock)
> context::C::Block is used to generate declarations for translation of functions.
> Functions are const, so they cannot be reassigned, but the fact that (expression) blocks,
> functions and if..else expressions might return different functions based on runtime state
> means, that for each such function, there must be multiple definitions in the C code
> for different alternatives of the function body implementation, its return types and capture types.
> All of this is accumulated in context::C::Block when evaluating these compound "returning" expressions
> and later used to create actual definitions in context::C::Global.
>
> context::C ties all the above mentioned parts together.
> Like context::Cynth, new context::C linked to their parents are created to manage scope in the C code.
> All these contexts are linked to one context::C::Global context and one context::Cynth constext (which has its own hierarchy).
> There is no nesting of context::Cynth contexts in nested context::C contexts -
> they are just two parallel constructs linked to each other.
> context::C contains local allocations (main or any user-defined functions) and declaratons
> (with C scope rules - functions and blocks).
> The linked context::C::Global stays the same during the whole translation process.
> The linked context::Cynth may change to a new deeper nested (child) context or go back to its parent.
> Memory management of the contexts linked by reference is left to the caller.
> The global context and the root compilation context are only allocated once,
> while the nested compilation contexts should be all declared on the stack of functions handling the current
> operation that needs the nesting.
