# Major issues

* Fix the syntax error.
* Add errors to the parser.
* Fix esl::compose or remove its use everywhere.
* fix the segfaults with strings not wrapped in components..  
    Maybe the problem was with the esl::join function (with a single value to join).  
    Check if it's fixed or if the problem can be traced to the esl::join function.

# Makefile

* Include clean-up (careful with sem/declarations).
* Link object files selectively.
* Don't forget about the clang sanitizer and other debug options in the makefile.
* Don't forget about the comented out part to link all cpp files.

# C++ details

* `std::move` when defererencing results.
* Check places where return std::move could mess with copy elision.
* Check if everything is ok with stuff that uses `std::vector<bool>`.  
    Or i could use char instead of bool (using cynth::boolean = char) - `std::vector<char>` is no special case.
* Use `*std::get_if<T>(variant)` instead of `std::get<T>(variant)` to avoid checking.  
    Or maybe even that doesn't avoid a check?
* Std::move(*result) instead of *std::move(result)?  
    Nope, move(*result) is ok as well as move(*optional) etc.  
    However, on raw pointers (or other non-owning referential types) it must be the other way around *move(ptr).
* How come, that i need to handle delete and new for incomplete component types manually, but it just somehow works for std::vector of incomplete types?
* Check if `return decltype(auto)` used where needed (esp. in lift).
* `std:forward` when calling perfectly forwarded callables.
* TODO: Move or ref in chained lifts?

# Naming

# Structure

* Sort out no longer relevant test files.

# Implementation

* Constexpr string values for errors in results.  
    C++20 std libraries should implement constrexr std::string, but no compiler besides MSVC does that right now.
    String views are not really usable out of the box in this case.
    The simplest solution would be to store constexpr char const * values for every possible error message.
* Not only strings (a major issue at the top), but other nodes should be held directly with no `component` indirection.

## Semantics

* Do I really need `component_vector`s? wouldn't `std::vector`/`esl::tiny_vector` be enough?  
    There definitely was a reason why I used `component_vector`s,
    but could it have be related to the currently resolved circular dependecy issues?
* Encapsulation.
* `type.complete()` returns result, but optional makes more sense.  
    I think there were complications with `vector<optional<result<...>>>` kind of thing though.
    (`vector<result<result<...>>>` would colapse into `vector<result<...>>`.)  
    Yeah maybe i'll keep it the way it is.  
    Maybe i should restrict return types to `result<vector<...>>` - not alowing `vector<result<...>>`.
* In lift for two vectors, iterate over the size of the smallest one to avoid out of bounds access.  
    Returning an error now, when trying to iterate over differently sized vectors.  
    This introduces more mess with `result<vector<result<...>>>` and similar constructs.
* Remove the non-copyable option from categories (it was there only for tighter checks during initial development).

## Syntax

* I don't like the deeply nested lambdas to branch out on different variant alternatives.  
    I usually get rid of nested branches by structuring my code like `if (a) { ...; return; } ...;`
    instead of `if (a) { ...; } else { ...; }` but that is not applicable to the lambdas.
    One thing that comes to mind would be some overloaded operators to be used like syntax sugar over `esl::lift`.
* I should stop using lift over `target::component`. It's a lot more verbose, than just dereferencing the component.  
    lift over `target::optional_component` or `target::component_vector` does make sense though.

# Cynth

* I guess I could allow not explicitly returning from block expressions which would indicate a default value.  
    Declared variables with no explicit initialization are implicitly initialized to some default value (zero initialized)
    so maybe the same could be done with block expressions.
    However, it would mean that a block expression with no return would carry no type, value or expression until it is assigned or returned from a function
    while a block expression with a conditional return (i.e. it returns but not always) would carry a type and potentially a default value or expression for that type.
    The first case could be complicated to implement, but the second should be relatively simple.
    So maybe I'll just allow block expressions to return "sometimes", but not "never".
    Return "never" would be a compilation error, while return sometimes would be at most a compilation warning and zero initialization at run-time (or compile-time evaluation).
    This would also fit with the idea of an implicit `return ()` in block expressions returning void - `()` would be the default initialization of type `()`.
    Block expression that returns `()` "sometimes" will implicitly return the default value of `()` type (i.e. the `()` value) at the end of the block.
    Block expression that never returns will implcitly be set to return the `()` type and thus will always return the `()` value.
    With such semantics, `$ a = {}` would be an error, because a `()` type variable cannot be declared,
    while `$ a = { if (x) return 1; }` is ok and infered as `Int` with an implicit `return 0`
    and, also, `() f () {}` is ok since `()` type can be returned from functions.
* `self` keyword refering to the current function (from within its body) for recursion.  
    With the current semantics, a function's name is not in context inside of its body.
* Decide about implicit conversions.
* Negative indices?
    Negative indexing from the back of an array could definitely be useful, but should be an opt-in feature
    in the sense, that something like `a[-1]` shouldn't be indexing from the back by itself because that would introduce overhead where such idnexing isn't necessary.
    I could introduce a new keyword for a new kind of array element. Something like `back` or `rev`.
    `a[back i]` would be equivalent to `a[n - 1 - i]` for a `T [n] a` array.
    So `0` would refer to the last index, unlike in many languages, where `-1` refers to the last index.
    `a[0, back 0, 1, back 1]` for `a == [a, b, c, d]` would result in `[a, d, b, c]`.
    Maybe I could combine `back` with `to` e.g. `a[0 to back 1]` (`[a, b, c]`) or `a[back 0 to 1]` (`d, c, b`).
    Grammar for `<array_elem>`: `back <expr>`, `<expr> to <expr>`, `back <expr> to <expr>`, `<expr> to back <expr>`, `back <expr> to back <expr>` and the last four again with `... by <expr>`.
* lambda capture (just copy the whole context for now)
* composed assignment operators  
    `+=` `-=` `*=` `/=` `**=` `%=` `&&=` `||=`
* buffers aren't non-const by definition... their elements are non-const, but aren't directly assignable anyways  
    assignment to a buffer would mean a switch to a different generator, which is something that i still haven't thought through completely  
    this should be taken care of now
* reading input variables should be impossible at compile time  
    passing referential input variables should be possible though
* decide on consistent "compconst" terminology and semantics
* should I call `()` the empty type instead of the void type?
* where is a void-typed value ok semantically?  
    syntactically, `()` can appear in function applications (`f()`) and in return statements `return ()` (equivalent to just `return`)  
    but is it ok to do something like this: `f(g())` or `return g()` wrere `g()` returns `()`?  
    I guess it could be useful in generic code (in future versions) so I'll allow it for now.

# Some old TODOs

* solve the makefile includes problem
* iterate over buffers in reverse
