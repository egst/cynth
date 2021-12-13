# Omiting compconst value declarations

This optimization might be useless in many cases since any reasonable C compiler will perform these as well.
However, they might help with unnecessary compconst array copies, and might also speed up the compilation a little.

```
# `var(name, entry, ...)` inserts a compile-time variable tuple entries
# `local(string)` inserts a local statement
# `static(string)` inserts a static (global) declaration
# `function(string)` inserts a function-level declaration
# `value = ...` indicates the value on the lhs of a definition

# assume a runtime variable `Int t`

# Simple types:

# non-comp value, non-const (target) type:
Int a = t;
> value = ResolvedValue{type::Int{}, 't'}
> local('cth_int var = t;')
> var('a', ResolvedValue{type::Int{}, 'var'})

# comp value, non-const type:
Int a = 1;
> value = ResolvedValue{type::Int{}, value::Int::make(1)}
> local('cth_int var = 1;');
> var('a', ResolvedValue{type::Int{}, value::Int::make(1)})

# non-comp value, const type:
Int const a = t;
> value = ResolvedValue{type::Int{}, 't'}
> local('cth_int var = t;')
> var('a', ResolvedValue{type::Int{}, 'var'})

# comp value, const type:
> value = ResolvedValue{type::Int{}, value::Int::make(1)}
Int const a = 1;
> var('a', ResolvedValue{type::Int{}, value::Int::make(1)})

# Simple IO types:
# Note: translateValue(value::In{type::Int{}, 'inval'}) -> '((int const) inval)'

Int in a;
> static('cth_int inval = 0;')
> var('a', ResolvedValue{type::In{type::Int{}}, value::In::make(type::Int{}, 'inval')})

# assume `Int in a`
Int in b = a;
> value = ResolvedValue{type::In{type::Int{}}, value::In::make(type::Int{}, 'inval')}
> var('b', ResolvedValue{type::In{type::Int{}}, value::In::make(type::Int{}, 'inval')})

# TODO (out)

# Arrays:

# TODO

# Buffers:

# TODO (in, out, basic)

# Functions:

# assume `Int a = t`
Int (Int) f = Int fn (Int x) x + 1
> static('cth_ret_{n} cth_fun_{n} (cth_ctx_{n} const * ctx, cth_int arg) { ... }') # simplified
> local('cth_ctx_{n} var_f = {.a = a};') # simplified
> var('f', ResolvedValue{type::Function{{type::Int{}}, {type::Int{}}}, value::Function::make('cth_fun_{n}', 'var_f')})
# TODO: Omiting fully compconst contexts? Omiting compconst parts of contexts?
```
