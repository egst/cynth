## The general idea:

```
Name      = String
Expr      = String
TypedExpr = {Type, Expr}

# nodes - syntactic AST nodes

# * resolve: AST node -> semantic structure  (compile-time)
# * evaluate, execute: expressions are evaluated, statements are executed (compile-time)
# * translate: * -> C code (run-time)
# * process: evaluate/execute or translate (run-time or compile-time)

# translating into C code or evaluating/executing them at compile-time:
# nodes:
processStatement    (Node) -> ()
processExpression   (Node) ->  (Value | TypedExpr)
processArrayElement (Node) -> [(Value | TypedExpr)]
# semantic structures:
processDefinition  (Type, ResolvedValue)         -> ()
processDeclaration (Type)                        -> ()
processAssignment  (Type, ResolvedValue, Target) -> ()

# resolving nodes into semantic structures:
resolveType              (Node) -> Type
resolveDeclaration       (Node) -> Declaration
resolveRangetDeclaration (Node) -> RangeDeclaration

# translating semantic structures into C code:
translateValue (Value) -> TypedExpr
translateType  (Type)  -> Name

# operations on semantic structures for compile-time values:
convertValue (Value, Type) -> Value
valueType    (Value)       -> Type
get          (Value) <Out> -> Out

# operations on semantic structures for types:
sameType   (Type, Type) -> Bool
commonType (Type, Type) -> Type
typeName   (Type)       -> String

# constructing specific parts of C code:
translateConversion  (Type, TypedExpr)  -> TypedExpr

# other operations on nodes:
extractNames     (Node) -> [Name]
extractTypeNames (Node) -> [Name]

# TODO: translateAllocation
# Maybe it shouldn't even be a part of the interface
```

# Interface

```c++ pseudo code
Vector          = std::vector
Optional        = std::optional
String          = std::string
Result          = esl::result
OptionalResult  = esl::optional_result
Tuple           = esl::tiny_vector
Context         = context::C
Value           = sem::CompleteValue
Type            = sem::CompleteVector
ResolvedValue   = sem::ResolvedValue
ResolvedTarget  = sem::ResolvedTarget
TypedExpression = sem::TypedExpression
TypedName       = sem::TypedName
Expression      = String
Name            = String
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

// Direct translation or compile-time evaluation:
// Results in a tuple vector containing intermediate structures of compile-time values or strings of C expressions.
<interface::node T> Result<Tuple<ResolvedValue>> precessExpression (Context &) (T)
// Results in a vector of tuple vectors containing the same values as precessExpression.
<interface::node T> Result<Vector<Tuple<ResolvedValue>>> processArrayElement (Context &) (T)
<interface::node T> Result<void> processStatement (Context &) (T)
<interface::type T> Result<> processDefinition (Context &, ResolvedExpression definition) (T)
<interface::type T> Result<> processDeclaration (Context &) (T)
// Retrieves the target's type and calls the implementation method on it.
Result<> processAssignment (Context &) (ResolvedValue, ResolvedTarget)

<interface::node T> Result<Vector<Name>> extractNames (T)
<interface::node T> Result<Vector<Name>> extractTypeNames (T)

// Resolution of other AST nodes to intermediate structures:
<interface::node T> Result<Tuple<Type>> resolveType (Context &) (T)
<interface::node T> Result<Tuple<CompleteDeclaration>> resolveDeclaration (Context &) (T)
<interface::node T> Result<Tuple<CompleteRangeDeclaration>> resolveRangeDeclaration (Context &) (T)
<interface::node T> Result<Tuple<ResolvedTarget>> resolveTarget (Context &) (T)

// Operations on types and compile-time values in intermediate structures:
// Only simple types have a name given directly with a constant. (e.g. `bool`)
<interface::type T> Name directTypeName (Context &) (T)
// More complex types - currently only simple const types. (e.g. `bool` or `bool_const`)
<interface::type T> Name typeName (T)
<interface::type T, interface::type U> bool sameType (T, U)
<interface::type T, interface::type U> Result<Type> commonType (T, U)
<interface::value T> Result<Out> get <Out> (Context &) (T)
<interface::value T> Result<Type> valueType (Context &) (T)
<interface::value T, interface::type U> Result<Value> convertValue (Context &) (T, U)

// Translation from intermediate structures:
<interface::value T> Result<TypedExpression> translateValue (Context &) (T)
<interface::type T> Result<TypedExpression> translateType (Context &) (T)

// Constructing translated C code from intermediate structures:
// Results in a C expression.
<interface::type T, interface::type U> Result<TypedExpression> translateConversion (Context &, TypedExpression from) (T, U)
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
<interface::node T> Result<Tuple<ResolvedValue>> T::precessExpression (Context &)
<interface::node T> Result<Vector<Tuple<ResolvedValue>>> T::processArrayElement (Context &)
<interface::node T> Result<Tuple<Type>> processType (Context &) (T)
<interface::node T> Result<void> T::processStatement (Context &)
<interface::node T> Result<Tuple<CompleteDeclaration>> T::resolveDeclaration (Context &)
<interface::node T> Result<Tuple<CompleteRangeDeclaration>> T::resolveRangeDeclaration (Context &)
<interface::node T> Result<Tuple<ResolvedTarget>> T::resolveTarget (Context &)
<interface::node T> Result<Vector<Name>> T::extractNames ()
<interface::node T> Result<Vector<Name>> T::extractTypeNames ()

// Types:
<interface::type T> char const * T::directTypeName // ideally constexpr
<interface::type T> Name T::typeName ()
<interface::type T, interface::type U> bool T::sameType (U) // or the other way around: T::sameType (T)
<interface::type T, interface::type U> Result<Type> T::commonType (U) // or the other way around: T::commonType (T)
<interface::type T> Result<Name> T::translateType (Context &)
<interface::type T> Result<> T::processDefinition (Context &, Optional<ResolvedValue> definition) // implements both processDefinition and processDeclaration
<interface::type T, interface::type U> Result<TypedExpression> T::translateConversion (Context &, U, TypedExpression from) // or the other way around: U::translateConversion (..., T, ...)
<interface::type T> Result<> T::processAssignment (Context &, ResolvedValue value, ResolvedTarget target)

// Values:
<interface::value T> Result<Out> T::get <Out> (Context &)
<interface::value T> Result<Type> T::valueType (Context &)
<interface::value T, interface::type U> Result<Value> T::convertValue (Context &, U)
<interface::value T> Result<TypedExpression> T::translateValue (Context &)
```

## File structure:

```c++ pseudo code
#include "interface/common.hpp" // interface::any related
#include "interface/nodes.hpp"  // interface::node related
#include "interface/types.hpp"  // interface::type related
#include "interface/values.hpp" // interface::value related; requires interface/types.hpp
```
