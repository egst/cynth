# ESL - Extended Standard Library

This directory contains various helper functions and types that are generic enough to be reused in other projects.
Everything here is located in the top-level `::esl` namespace and has no dependencies from `::cynth`.

## Boolean

This one could be moved to 'containers' as it only contains a few functions
to work with containers (ranges or lists of types) of boolean values.

## Category

A wrapper for `std::variant` that provides some additional constructors and assignments
and also getters that return `esl::result_error` instead of throwing, like `std::get` does with `bad_variant_access`.

## Component

Pointers to dynamically allocated values that perform clean-up (`delete`) atomatically.
This is essentially like `std::unique_ptr` that allows copies (full copy of the underlying object, not the pointer)
and allows working with incomplete types (if `component_deleter` and `component_allocator` are later implemented).

Provides `component` for a single value (non-nullable pointer),
`optional_component` for a single potentially missing value (nullable pointer)
and `component_vector` for multiple values
(`component_vector` with underlying `std::vector` container, `tiny_component_vector` with `esl::tiny_vector`
and `basic_component_vector<vector>` for any selected underlying `vector` container type).

## Concepts

Generic concepts.

## Containers

Generic operations on various containers. Most often used are `unite_results`
to transform `vector<result<T>>` to `result<vector<T>>` (`unite_optionals` etc.)
and `single` to assert a single valued vector and return its only value.

## Debug

Provides the `inspector` struct to display a type
during compilation - works great with clangd language server
to inspect types right in the editor.
See `macros.hpp` for shorthand macro functions.

## Functional

Various constructs to work with functions. Most often used are `overload`
to create an overload set from lambda functions (without the need for explicit functor [^1] struct declarations)
and `fuctor` to wrap regular functions (function pointers/references) into functors.

[^1]: Functor, as in a C++ structure with an overloaded `operator ()`, not the functional programming functor/applicative/monad construct.

## Iterator

A helper structure for iterator implementations with no boilerplate.

## Lazy

A lazy-evaluated value. Not used currently.

## Lift

A simplified lift (as in functional programming "lambda lifting") implementation.
The goal is not to mimic Haskell and other FP languages precisely, but to allow generalizing functions for
various "wrapper" structures without going too "FP" crazy in a language, that isn't really meant to be FP.
Structures that want to allow lifting over them implement their own specialization that is selected
with an empty `target` tag structure. `lift<target::optional>(f)` transforms a `B (A)` function
into a `std::optional<B> (std::optional<A>)` (mimicking `lift` over `Maybe` in Haskell),
but others might be more specific and perform some "merging" of nested result "wrappers" or
iteration over "zipped" containers with `lift<target::vector>(f)(a, b)` etc.
There is no "applicative" construct, so there are no utilities to use e.g.
`optional<int (int)>` as a function without unwrapping it manually.

See `sugar.hpp` for additional syntax sugar (overloaded operators) for lift.

## Macros

Provides macros `ESL_INSPECT` and `ESL_INSPECT_TYPE` for shorter and simpler syntax of the `inspector` structure.

## Math

Currently only contains a `pow10` function used in custom string to number parsing.

## Optional

Various tools related to `std::optional`.

## Ranges

Concepts for generic ranges and some more specific containers (e.g. `sized_range`, `insertable_range` etc.)
and `range_value_type` to get the underlying type of any range.
Also provides the `nullrange` structure - a dummy always empty range for use in generic code.

## Result

Like `std::optional`, but with an error message instead of an empty value (like `Either` in Haskell).
Provides `result` for a simple value/error situation, `optional_result` for value/error/nothing
and `reference_result` to hold the value referentially.

## String

Various tools related to `std::string`.

## Sugar

Syntax sugar for `lift.hpp`.

## Tiny_vector

A vector optimized for the zero or one value cases. Contains an `std::optional` for the first value and `std::vector` for the rest.
Used to implement any kind of tuples in Cynth, to avoid dynamic allocation in the single-valued cases.

## Tuple

Various tools related to `std::tuple`.

## Type_manip

Various tools for type manipulation.

## Variant

Various tools related to `std::variant`.

## View

A non-owning view over a range given by two iterators.

## Zip

A "zipped" view over multiple containers.
Provides `zip(a, b, c)` to iterate over e.g. `auto const & [e, f, g]` elements and
`enumerate(a, b, c)` to iterate over the same elements as with zip but with an additional integral index
counting from 0, e.g. `auto const & [i, e, f, g]`.
