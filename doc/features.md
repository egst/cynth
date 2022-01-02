# Cynth features

This document contains notes on various Cynth features, that are yet to be implemented
or might be implemented in a simplified form in the first version.

## Range declarations

```cth
for (
    Int i in [1, 2],                    # 0
    (Int i, Int j) in [(1, 2), (3, 4)], # 1
    (Int i, Int j) in ([1, 2], [3, 4]), # 2
    ((Int, Int) i, Int j)   in ([(1, 2), (3, 4)], [5, 6]), #3
    ((Int i, Int j), Int k) in ([(1, 2), (3, 4)], [5, 6]), #4
    (Int i, Int j, Int k)   in ([(1, 2), (3, 4)], [5, 6])  #5
)
```

* `0:` This simplest case is implemented currently.  
    "Zip" iteration can be represented with a list of such range declarations.
* `1:` Arrays of tuples will not be implemented in the first version, so this case is not considered.
* `2:` This won't be implemented in the first version, but it could replace the need for multiple range
    declarations (e.g. `for (decl, decl, ...)`) as it also represents the zip functionality.  
    So in future versions, there will probably be a backwards-incompatible change of removing this.
    The list of multiple range declarations might be later reused for the cartesian product. E.g.
    `for ((Int i, Int j) in [a, b])` will perform a zip iteration over pairs of sequentially corresponding elements
    while `for (Int i in a, Int j in b)` will perform a product iteration over all pairs of elements.
* `3:` This shows how zip iteration over arrays of tuples can be represented.
* `4:` Even the tuples inside of arrays can be "unpacked".
* `5:` Tuples are always flat, so this is actually semantically equivalent to #4

## Other single-valued tuples

```cth
when (a, b, c) {}
```

The condition in `when`, `if` and `while` is syntactically just an explicitly parenthesized tuple of values.
However, semantically it is restricted to a single value.
This isn't really consistent with the rest of the language, as every expression, type or declaration is a tuple.
(Only statements are not tuples. Though they can be grouped into blocks and singular statements are semantically
equivalent to single-statement blocks in the same way singular expressions are equivalent to single-value tuples.)
Some of them are explicitly parenthesized, some are not, but other than that there is no fundamental difference.
The only difference is, that I haven't come up with semantics for some cases.
In many of those cases there is really no need to have tuple semantics there,
but it would just make everything cleaner without exceptions from the "everything is a tuple" semantics.

Here are all the constructs that currently (in the first version) require a single value:

```cth
if    (<value>) <values> else <values> # if..else
when  (<value>) <statement>            # when
while (<value>) <statement>            # while

<value>(<values>) # function call
<value>[<value>]  # subscript
<type> [<value>]  # array element type

[<value> to <value>]            # from..to array element
[<value> to <value> by <value>] # from..to..by array element
[...<value>]                    # spread array element
```

## Functions

Function application with multiple function values could have some useful semantics.
For example, it could represent function composition:

```cth
(f, g)(a, b)
# equivalent to:
g(f(a, b))
```

There is a slight drawback, that the `<types>(<values>)` syntax indicates that types can be seen as functions,
that convert their arguments. However, the composition semantics make no sense for types as well as
the tuple semantics make no sense for functions (because they already take and return different numbers of values),
so I think it should be ok.

An alternative would be to reserve it for something like function overloading, in the sense that
`(f, g)(a)` would try to apply one of the two functions and chose the one that better fits the type of `a`.

```cth
(Int (Int), Float (Float)) f = (
    Int   (Int   x) x + 1,
    Float (Float x) x + 1.,
);
```

## Subscripts

Semantics of subscripts with multiple indices are planned, but their implementation might be skipped for the first version.
Multiple indices would select a sub-array (by value/copy). Other array elements can also be used as subscript indices:

```
a[1, 2, 10 to 15]
# equivalent to:
[a[1], a[2], a[10], a[11], a[12], a[13], a[14]]
```

Empty subscript copies the whole array:

```cth
a[]
# equivalent to:
# Int [n] a;
a[0 to n]
```

This also works for assignment targets:

```cth
a[1, 2] = [3, 4]
# equivalent to:
a[1] = 3;
a[2] = 4;

a   = [1, 2, 3]; # assignment of a new reference
a[] = [1, 2, 3]; # assignment to the referenced values

a   = b;   # assignment by reference (new reference)
a   = b[]; # assignment by value     (new reference)
a[] = b[]; # assignment by value     (to the referenced values)
```

*Note that targets are not l-values, they are not values at all. So it's not that a subscript
sometimes returns a value and sometimes a reference, it's just that there is a subscript on values (expressions)
and subscript on targets (names or subscripted names (to allow multi-dimensional arrays in the future)).
One produces values (expressions), the other one produces targets.*

There is a drawback, that this actually make the semantics more complex with some special cases.
Subscript can now return both a simple value and an array value
and there is no way to return a single-valued or zero-valued array.
On the other hand, there is no need for single-vlaued or zero-valued arrays.
Single-valued arrays might have a use-case in the future, when arrays will be allowed to contain referential values,
but until then, a single-valued array is just a simple value with more complicated access to it.
I should keep an eye on this though, and if it begins to introduce more exceptions and mess into the language,
I will have to remove this, and come up with a different syntax for subscripting sub-arrays.

Subscripts on a tuple of arrays could simply return a tuple of values (or sub-arrays):

```
(a, b)[n]
# equivalent to:
(a[n], b[n])
```

## Range array elements

Tuples in range array elements will be useful, once I allow arrays of tuples.

```cth
[(0, 0.) to (10, 1.) by (1, .1)]
# equivalent to:
[(0, 0.0), (1, 0.1), (2, 0.2), ..., (8, 0.8), (9, 0.9)]

[...([1, 2, 3], [1., 2., 3.)]
# equivalent to:
for (Int a in [1, 2, 3] Int b in [1., 2., 3.]) (a, b)
# equivalent to:
[(1, 1.), (2, 2.), (3, 3.)]
```

## Conditions

The obvious choice of semantics for tuples of condition in the if, when and while constructs
is either a conjunction or a disjunction. I'll choose conjunction, but I'll keep disjunction as a possibility.
At a first glance, `if (a, b, c)` seems like an unnecessary alternative syntax with no benefit over `if (a && b && c)`.
But it becomes actually useful for tuples that are not "unpacked", e.g:

```cth
(Bool, Bool, Bool) check () { ... };

when (check()) { ... };
# equivalent to:
(Bool a, Bool b, Bool c) = check();
if (a && b && c) { ... };
```

This makes `if (t)` a check for "all true". Other variations, such as "all false", "some true" and "some false"
can be achieved in the following way:

```cth
$ checks = check();
Bool allTrue   = if  (checks) true  else false;
Bool someFalse = if  (checks) false else true;
Bool allFalse  = if (!checks) true  else false;
Bool someTrue  = if (!checks) false else true;
```

# Recursion

Recursion is currently not possible, but I plan to add a `self` keyword for that purpose:

```cth
Int (Int) factorial = Int fn (Int x) if (x == 0) 1 else x + self(x - 1);
```

I don't have any ideas yet about mutual references between functions...

```cth
(Int (Int) f, Int (Int) g) = {
    Int (Int) (Int (Int)) f = Int (Int) fn (Int (Int) g)
        Int fn (Int x) if (x == 0) 1 else x * g(x - 1);

    Int (Int) (Int (Int)) g = Int (Int) fn (Int (Int) f)
        Int fn (Int x) if (x == 0) 1 else x + f(x - 1);

    return (f(g(...)), g(f(...))); # TODO: How to represent this?
};
```
