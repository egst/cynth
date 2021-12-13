# Interface

```c++ pseudo code
Vector         = std::vector
Optional       = std::optional
String         = std::string
Result         = esl::result
OptionalResult = esl::optional_result
Tuple          = esl::tiny_vector
Context        = context::C
Value          = sem::CompleteValue
Type           = sem::CompleteVector
ResolvedValue  = sem::ResolvedValue
ResolvedTarget = sem::ResolvedTarget

interface::any  = /* any ast node or a semantic structure */
interface::node = /* any ast node */
```

## Interface:

All translating functions only return a string of C to represent an expression.
Any generated C statements are inserted into the provided context as a side-effect.

All of the interface functions are curried in a specific way to separate a unary or binary function
accepting the main targets, that might need to be lifted over.
E.g. `lift<target>(f(context, config...))(targets...)(args...)`

```c++ pseudo code
// For debug or source reconstruction:
<interface::any T> String display (T)
// Displays single values directly and tuples explicitly parenthesized (e.g. `a` and `(a, b, c)`):
<interface::any T> String displayTuple (T)

// Direct translation or compile-time evaluation of AST nodes:
// The `translate` parameter forces translation instead of evaluation.
// Results in a tuple vector containing intermediate structures of compile-time values or strings of C expressions.
<interface::node T> Result<Tuple<ResolvedValue>> resolveExpression (Context &, bool translate) (T)
// Results in a vector of tuple vectors containing the same values as resolveExpression.
<interface::node T> Result<Vector<Tuple<ResolvedValue>>> resolveArrayElement (Context &, bool translate) (T)
<interface::node T> Result<void> resolveStatement (Context &) (T)
<interface::node T> Result<Tuple<Type>> resolveType (Context &) (T)
<interface::node T> Result<Vector<String>> extractNames (T)
<interface::node T> Result<Vector<String>> extractTypeNames (T)

// Resolution of other AST nodes to intermediate structures:
<interface::node T> Result<Tuple<CompleteDeclaration>> resolveDeclaration (Context &) (T)
<interface::node T> Result<Tuple<CompleteRangeDeclaration>> resolveRangeDeclaration (Context &) (T)
<interface::node T> Result<Tuple<ResolvedTarget>> resolveTarget (Context &) (T)

// Operations on types and compile-time values in intermediate structures:
// Only simple types have a name given directly with a constant. (e.g. `bool`)
<interface::type T> String directTypeName (Context &) (T)
// More complex types - currently only simple const types. (e.g. `bool` or `bool_const`)
<interface::type T> String typeName (T)
<interface::type T, interface::type U> bool sameType (T, U)
<interface::type T, interface::type U> Result<Type> commonType (T, U)
<interface::value T> Result<Out> get <Out> (Context &) (T)
<interface::value T> Result<Type> valueType (Context &) (T)
<interface::value T, interface::type U> Result<Value> convertValue (Context &) (T, U)

// Translation from intermediate structures:
<interface::value T> Result<String> translateValue (Context &) (T)
<interface::value T> Result<String> translateTarget (Context &) (T)
<interface::type T> Result<String> translateType (Context &) (T)

// Constructing translated C code from intermediate structures:
// --The last curried parameters expect strings of C expressions.-- Nope, that's unnecessarily complicated.
// Results in a C variable name, or nothing (nullopt) when no declaration was made. (Compconst values are not declared in the C code.)
<interface::type T> Result<ResolvedValue> translateDefinition (Context &, Optional<Sting> definition) (T)
// Results in an expression refering to the allocated data. (e.g. `global_var.data`)
<interface::type T> Result<String> translateAllocation (Context &, Optional<Sting> initialization) (T)
// Results in a C expression.
<interface::type T, interface::type U> Result<String> translateConversion (Context &, String from) (T, U)
```

## Implementation:

The interface functions call implementations that are defined as member methods of corresponding structures.
In case of two semantically equivalent targets, e.g. `commonType`, either one (but not both) of the targets
must implement it and the symetric case will be generated automatically (at compile time with templates).
In case of two different targets, e.g. `convertValue`, the one choosen statically by the interface must implement it.

```c++ pseudo code
// All:
<interface::any T> String T::display ()

// Nodes:
<interface::node T> Result<Tuple<ResolvedValue>> T::resolveExpression (Context &, bool translate)
<interface::node T> Result<Vector<Tuple<ResolvedValue>>> T::resolveArrayElement (Context &, bool translate)
<interface::node T> Result<Tuple<Type>> resolveType (Context &) (T)
<interface::node T> Result<void> T::resolveStatement (Context &)
<interface::node T> Result<Tuple<CompleteDeclaration>> T::resolveDeclaration (Context &)
<interface::node T> Result<Tuple<CompleteRangeDeclaration>> T::resolveRangeDeclaration (Context &)
<interface::node T> Result<Tuple<ResolvedTarget>> T::resolveTarget (Context &)
<interface::node T> Result<Vector<String>> T::extractNames ()
<interface::node T> Result<Vector<String>> T::extractTypeNames ()

// Types:
<interface::type T> char const * T::directTypeName // ideally constexpr
<interface::type T> String T::typeName ()
<interface::type T, interface::type U> bool T::sameType (U) // or the other way around: T::sameType (T)
<interface::type T, interface::type U> Result<Type> T::commonType (U) // or the other way around: T::commonType (T)
<interface::type T> Result<String> T::translateType (Context &)
<interface::type T> Result<ResolvedValue> T::translateDefinition (Context &, Optional<Sting> definition)
<interface::type T> Result<String> T::translateAllocation (Context &, Optional<Sting> initialization)
<interface::type T, interface::type U> Result<String> T::translateConversion (Context &, U, String from) // or the other way around: U::translateConversion (..., T, ...)

// Values:
<interface::value T> Result<Out> T::get <Out> (Context &)
<interface::value T> Result<Type> T::valueType (Context &)
<interface::value T, interface::type U> Result<Value> T::convertValue (Context &, U)
<interface::value T> Result<String> T::translateValue (Context &)
<interface::value T> Result<String> T::translateTarget (Context &)
```

## File structure:

```c++ pseudo code
#include "interface/common.hpp" // interface::any related
#include "interface/nodes.hpp"  // interface::node related
#include "interface/types.hpp"  // interface::type related
#include "interface/values.hpp" // interface::value related; requires interface/types.hpp
```
