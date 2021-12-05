# Major issues

* fix the syntax error
* add errors to the parser
* fix esl::compose or remove its use everywhere
* fix the segfaults with strings not wrapped in components

# Makefile

* include clean-up (careful with sem/declarations)
* link object files selectively
* don't forget about the clang sanitizer and other debug options in the makefile
* don't forget about the comented out part to link all cpp files

# C++ details

* check places where return std::move could mess with copy elision
* check if everything is ok with stuff that uses `std::vector<bool>`  
    or i could use char instead of bool (using cynth::boolean = char) - `std::vector<char>` is no special case
* use `*std::get_if<T>(variant)` instead of `std::get<T>(variant)` to avoid checking  
    or maybe even that doesn't avoid a check?
* std::move(*result) instead of *std::move(result)?  
    nope, move(*result) is ok as well as move(*optional) etc.  
    however, on raw pointers (or other non-owning referential types) it must be the other way around *move(ptr)
* how come, that i need to handle delete and new for incomplete component types manually, but it just somehow works for std::vector of incomplete types?
* check if `return decltype(auto)` used where needed (esp. in lift)

# Naming

* rename sem::value::(Array|Buffer|In|Out).value->value to something less generic and ambiguous
* value::complete, type::complete is just confusing. change to complete_value to math other things like typed_value

# Structure

* sort out no longer relevant test files

# Implementation

* decide whether to keep type info in values, or to compute it every time. maybe it could be cashed in an optional value?
* constexpr string values for errors in results.  
    c++20 std libraries should implement constrexr std::string, but no compiler besides MSVC does that right now  
    string views are not really usable out of the box in this case  
    the simplest solution would be to store constexpr char const * values for every possible error message

# Semantics

* encapsulation
* type.complete() returns result, but optional makes more sense  
    i think there were complications with `vector<optional<result<...>>>` kind of thing though  
    (`vector<result<result<...>>>` would colapse into `vector<result<...>>`)  
    yeah maybe i'll keep it the way it is  
    maybe i should restrict return types to `result<vector<...>>` - not alowing `vector<result<...>>`
* in lift for two vectors, iterate over the size of the smallest one to avoid out of bounds access  
    returning an error now, when trying to iterate over differently sized vectors  
    this introduces more mess with `result<vector<result<...>>>` and similar constructs
* how to implement fallback overloads in lift without explicit requires (!...)  
    this might be taken care of
* remove the non-copyable option from categories (it was there only for tighter checks during initial development)
* buffer variable should only contain reference to the buffer value and its size  
    (which is the size of a view over the buffer, like with arrays),  
    while the buffer value should contain the actual values and the generator function  
    this way, the buffers may be passed by references that might refer to a smaller buffer

# Cynth

* decide about implicit conversions
* negative indices?
* lambda capture (just copy the whole context for now)
* composed assignment operators  
    `+=` `-=` `*=` `/=` `**=` `%=` `&&=` `||=`
* buffers aren't non-const by definition... their elements are non-const, but aren't directly assignable anyways  
    assignment to a buffer would mean a switch to a different generator, which is something that i still haven't thought through completely  
    this should be taken care of now
* reading input variables should be impossible at compile time  
    passing referential input variables should be possible though

# Some old TODOs

* solve the makefile includes problem
* iterate over buffers in reverse
