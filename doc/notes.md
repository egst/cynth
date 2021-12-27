# Misc. notes on translation

This file contains mostly just some brainstorming ideas on how to tackle translation
(or comp-time evaluation/execution) of different Cynth constructs.

## Translating names

Names related to cynth declarations in the final C code follow some conventions
set up in `sem/translation.hpp`, such as that locally allocated array values are prefixed with `val_`,
statically (globally) allocated input values with `inval_` etc. and all of them are end with a unique identifier.
For now, this identifier is a simple integer value that is counted and incrnmented
from the begining of the translation process with every new id request (with every new name).
This identifier is then appended as a decimal number to the names.
This could relatively quickly lead to rather large identifier names, so I'll encode it in hex or base64
or something like that to save some space, but for now I'm keeping it decimal.
Also, I could decrement the counted identifier back to some number before entering a block or a function or something,
but that could be unnecessarilly complicated.

In examples of translated code, instead of these unique identifiers, I'll use some ad-hoc made up names
that might (or might not) relate to some corresponding names in cynth.
This could be useful to implement in the actual translation process as well
so that the user (or more likely me, when testing and debugnig the compiler) could relate
the translated C code to their original Cynth code.

## Translating blocks and returns

Cynth blocks and returns can be translated pretty straightforwardly
with the use of some GNU extentions: statement expressions (`({})`) and local labels (`__label__`).

```cth
Int f (Int x) {
    Int a = {
        Int b = 1;
        when (x == 0) {
            return 1;
        };
        b = b + x;
        return b;
    };
    if (x == 1) {
        return 2;
    } else {
        x = x - 1;
    }
    return x * 2;
};

Int g (Int x) x + 1;
```

```c
inline cth_int fun_f (cth_int var_x) {
    return ({
        __label__ ret;
        cth_int result = 0;
        cth_int var_a = ({
            __label__ ret;
            cth_int result = 0;
            cth_int var_b = 1;
            if (cth_eq$int(var_x, 0)) {
                result = 1;
                goto ret;
            }
            var_b = cth_add$int(var_b, var_x);
            result = var_b;
            goto ret;
            ret: result;
        });
        if (cth_eq$int(var_x, 1)) {
            result = 2;
            goto ret;
        } else {
            var_x = cth_sub$int(var_x, 1);
        }
        ret: result;
    });
}

inline cth_int fun_g (cth_int var_x) {
    return cth_add$int(var_x, 1);
}
```

If expressions can be implemented in a similar way, except that there is no need for the goto jumps
because there are only two simple branches.

```cth
# runtime Bool x
Int a = if (x == 0) 1 else 2;
```

```c
cth_int var_a = ({
    cth_int result;
    if (x == 0) {
        result = 1;
    } else {
        result = 2;
    }
    result;
});
```

Note that the examples above don't account for:
* passing a structure of runtime captured values or any conditional function selection
* returning tuples
Update: Tuples and runtime functions values are described below.

# Translating tuple expressions

All built-in operators return the same kind of tuple as their arguments.
The translation of these happens "in paralel" - the individual tuple elements are processed separately with
the other corresponding arguments (e.g. `(1, 2) + (2, 3)` performs `1 + 2` and `2 + 3` separately).
So these can be simply translated into separate C expressions and variables.

On the other hand, functions, block expressions and if..else expressions might result in a tuple of any size.
In addition, functions take in any unrelated number of arguments.
So these will be translated into intermediate struct variables representing the tuples.

I could simply introduce a variable and later compute it in a nested scope, but that would
require me to keep track of the names of these "return" variables.
Instead I will translate these into GNU statement expressions with a nested "return variable", always called `result`,
and a nested local "return label", always called `ret`.
To avoid keeping track of the intermediate strutctures for return values, I'll declare a local structure,
always called `struct result`, while the resulting value on the outside will be declared as `__auto_type` (a GNU extension).
All the members will always be called `e0`, `e1`, `e2` and so on. so there will be no need to keep track of the structures
to know the member names either. (Note that (non-typedefed) structs' names are in a different "namespace"
and won't collide with variables or typedefed types as they must be referenced with `struct <name>`.)

```cth
# runtime Int x, Int y
(Int a, Int b) = { return (1, x) } + (2, y);
```

```c
// runtime cth_int var_x, var_y

// { return (1, 2) }
__auto_type var_t = ({
    struct result {
        cth_int e0;
        cth_int e1;
    };
    struct result result;
    __label__ ret;

    result.e0 = 1;
    result.e1 = var_x;
    goto ret;

    ret: result;
});

cth_int var_a = var_t.e0 + 2;
cth_int var_b = var_t.e1 + var_y;
```

There will be a lot of boilerplate code even for very simple cases, as shown above.
This shouldn't be a problem after compiling the C code though.
From experiments with GCC I've confirmed, that this kind of code is optimized away with -O1.

# Note on optimizations

Here's an interesting example: https://godbolt.org/z/cz7dar8MW

Notice the switch in the `fun_t` function:

```c
switch (ctx->branch) {
    case 0:
        __auto_type tupvar0 = fun_f(&ctx->data.v0);
        result.e0 = tupvar0.e0;
        break;
    case 1:
    //default:
        __auto_type tupvar1 = fun_g(&ctx->data.v1);
        result.e0 = tupvar1.e0;
        break;
    /*
    case 2:
        __auto_type tupvar2 = fun_f(&ctx->data.v2);
        result.e0 = tupvar2.e0;
        break;
    case 3:
        __auto_type tupvar3 = fun_g(&ctx->data.v3);
        result.e0 = tupvar3.e0;
        break;
    */
}
```

When there's up to two cases in the switch and one of them is set as default,
GCC with -O1 is able to optimize the branches away. However, with three or more cases,
or without the default case, the translated assembly is a little more complex with a simple function call to `fun_t`.

Also, for run-time inputs (which is what should probably matter more than comp-time input,
which should be relatively trivial to optimize for GCC) uncomment `var_a` that uses a run-time value from argv.

```c
int var_a = 7;
//int var_a = var_x;
```

TODO: Check what happens if I use `const` types where I can. Check what happens if I pass the context by value.

# Translating functions

```c
// 0: Generated on first function return encounter
// 1: Generated for the first  function return
// 2: Generated for the second function return
// 3: Generated for the third  function return

// Static:
struct cth_ret_f  { ... }; // 0
struct cth_ctx_f0 { ... }; // 1
struct cth_ctx_f1 { ... }; // 2
struct cth_ctx_f2 { ... }; // 3
struct cth_ctx_f  {        // 0
    int branch;
    union {
        cth_ctx_f0 e0; // 1
        cth_ctx_f1 e1; // 2
        cth_ctx_f2 e2; // 3
    } data;
};
cth_ret_f cth_fun_f0 (cth_ctx_f0 const * ctx, ...) { ... } // 1
cth_ret_f cth_fun_f1 (cth_ctx_f1 const * ctx, ...) { ... } // 2
cth_ret_f cth_fun_f2 (cth_ctx_f2 const * ctx, ...) { ... } // 3
cth_ret_f cth_fun_f  (cth_ctx_f  const * ctx, ...) {       // 0
    switch (ctx.branch) {
    case 0:
        return cth_ctx_f0(ctx.data.e0, ...); // 1
    case 1:
        return cth_ctx_f1(ctx.data.e1, ...); // 2
    case 2: default: // Default should indcate an implementation error, but let's keep it here for now.
        return cth_ctx_f2(ctx.data.e2, ...); // 3
    }
}

// Local:
__auto_type var_t = ({
    struct result {
        cth_ctx_f e0;
    };
    struct result result;
    __label__ ret;

    ...

    if (var_x) {
        result.e0 = (struct cth_ctx_f) {0, {...}}; // generates 0 & 1
        goto ret;
    }

    ...

    if (var_y) {
        result.e0 = (struct cth_ctx_f) {1, {...}}; // generates 2
        goto ret;
    }

    ...

    result.e0 = (struct cth_ctx_f) {2, {...}};     // generates 3
    goto ret;

    ...

    ret: result;
})
```

```cth
# runtime Int x;
Int (Int) f = {
    when (x == 0)
        return Int fn (Int x) x;
    return
        if (x > 0) {
            Int c = 1;
            Int g (Int x) x + c;
            g(x);
            return g;
        } else
            Int fn (Int x) x - 1;
};
```

```c
// internal
struct cth_tup$int {
    int e0;
};

// (1)
struct cth_ctx_g { cth_int c; }
typedef cth_tup$int cth_ret_g;
cth_ret_g cth_fun_g (cth_ctx_g const * ctx, cth_int arg_x) {
    struct cth_ret_g result;
    result.e0 = arg_x + ctx->c;
    return result;
}
// (2) -- could be optimized internally to avoid the trivial switch
struct cth_sctx_v { int branch; union { cth_ctx_g v0; } data; };
typedef cth_tup$int cth_sret_v;
cth_sret_v cth_sfun_v (struct cth_ctx_v const * ctx, cth_int arg_x) {
    switch (ctx->branch) {
    case 0: default:
        return cth_fun_g(ctx->data.v0, arg_x);
    }
}

__auto_type tupvar_t = ({ // block expression
    struct result { cth_ctx_t e0; };
    struct result result;
    __label__ ret;

    if (var_x == 0) {
        result.e0 = (struct cth_ctx_f) {0, {}};
        goto ret;
    }

    __auto_type tupvar_u = ({ // if expression
        // bctx = new branch context
        struct result { cth_ctx_u e0; };
        struct result result;

        if (var_x > 0) {
            __auto_type tupvar_v = ({ // if expression
                // bctx = new branch context
                struct result { cth_ctx_v e0; };
                struct result result;

                // `Int c = 1`
                cth_int var_c = 1;

                // `Int g (Int x) x + c`
                // comp g: val::Fun{{'x', 1}, `x + c`, {{}, {'c': {Int{}, 'c'}}}, 'ctxvar_g'}
                cth_ctx_g ctxvar_g = {.c = var_c};

                // `g(x)`
                // define cth_ret_g, cth_ctx_g, cth_fun_g (1)
                // note: translate(g) -> 'ctxvar_g'
                cth_fun_g(ctxvar_g, var_x);

                // `return g`
                // returning a function => bctx.nextBranch() -> 0
                result.e0.branch = 0;
                result.e0.data.v0 = ctxvar_g;
                goto ret;

                ret: result;
            }); // function returned => define cth_ret_v, cth_sctx_v, cth_sfun_v refering to cth_ctx_v, cth_fun_v (2)
            // bctx.nextBranch() -> 0
            result.e0.branch = 0;
            result.e0.data.v0 = tupvar_v.e0;
        } else {
            // bctx.nextBranch() -> 1
            result.e0 = (struct cth_ctx_g) {1, {}};
        }

        result;
    }); // function returned => 
    result.e0 = tupvar_u.e0;
    goto ret;

    ret: result;
});
cth_ctx_f var_f = tupvar_t.e0;
```

# For loops

```cth
# runtime Int [16] arr
# runtime Int x
Int a = {
    for (Int const e in arr) { # for:  returns Int, sometimes
        when (e == x)          # when: returns Int, sometimes
            return 1;
    };
    return 2;
};
```

```cth
# runtime Int [16] arr
# runtime Int x
Int a = {
    for (Int const e in arr) { # for:      returns Int, always (= in the first iteration)
        if (e == x)            # if..else: returns Int, always
            return 1;
        else
            return 2;
    };
};
```

This could be translated into:

```c
__auto_type tupvar_t = ({
    struct result { cth_int e0; } result;
    __label__ ret;
    {
        cth_int const var_e = var_arr[0];
        if (var_e == var_x) {
            result.e0 = 1;
            goto ret;
        } else {
            result.e0 = 2;
            goto ret;
        }
    }
    ret: result;
});
cth_int var_a = tupvar_t.e0;
```

```cth
# runtime Int [16] arr
# runtime Int x
Int a = {
    for (Int const e in arr) { # for:    returns [Int{1}], always (= in the first iteration)
        return 1;              # return: returns [Int{1}], always
    };
};
```

What about functions?

```cth
# runtime Int [16] arr
# runtime Int x
Int (Int) f = {
    for (Int const e in arr) { # for:      returns [Fun{...}, Fun{...}], always (= in the first iteration)
        if (e == x)            # if..else: returns [Fun{...}, Fun{...}], always
            return Int fn (Int x) x + 1;
        else
            return Int fn (Int x) x - 1;
    };
};
```

```cth
# runtime Int [16] arr
# runtime Int x
Int (Int) f = {
    for (Int const e in arr) { # for:      returns [Fun{...}], sometimes (= in the first iteration)
        when (e == x)          # if..else: returns [Fun{...}], sometimes
            return Int fn (Int x) x + 1;
    };
};
```

Seems like everythig should work OK. The general rule is, that for loop returns whatever its branches return.

What about mixed comp-time and run-time ranges?

```cth
Int [16] a;
Int [16] b;
for (Int i in [1 to 16], Int j in [1 to 32 by 2], Int e in a, Int f in b) {
    ...
}
```

```c
cth_int * var_a;
cth_int * var_b;
for (
    struct {
        cth_int pos;
        cth_int var_i;
        cth_int var_j;
    } iter = {0, 1, 1};
    iter.pos < 16;
    ++iter.pos,
    iter.var_i += 1,
    iter.var_j += 2
) {
    cth_int var_e = var_a[iter.pos];
    cth_int var_f = var_b[iter.pos];
    ...
}
```

# Optimizing for loops

```cth
Bool const a = {
    Int const b = 3;
    for (Int i in [1 to 5]) { # Loops that add no local statements can be executed in compile-time.
        when (i > b)
            return true;
    };
    return false;
};
```

```c
cth_bool const var_a = true;
```

```cth
Int j = 0;
Int const a = {
    for (Int i in [1 to 5]) { # Loops with comp-time ranges smaller than some threshold can be unrolled.
        j = j + i;
    }
    return 1;
};
```

This loop adds local statements, but the result of the block expression does not depend on it,
so while the loop will be translated, the `a` variable's value will be determined at compile-time.

```c
cth_int var_j = 0;
__auto_type tupvar_t = ({
    struct result {} result;
    __label__ ret;

    var_j = var_j + 1;
    var_j = var_j + 2;
    var_j = var_j + 3;
    var_j = var_j + 4;

    ret: result;
});
```

```cth
for (Int i in [1 to 10000]) { # Unrolling loops with large comp-time ranges might not be a good idea.
    j = j + i;
};
```

Unrolling a "large" loop would lead to large source files for the C compiler to compile and ultimately large executables.
However, simply allocating the range array would lead to the same problem.
The loop needs to be optimize into a simple `for (int i = <from>; i < <to>; i += <by>)` loop whenever possible.
If it's not possible, the array will be allocated, since that would probably have a similar spatial imprint
on the final executable while being simpler for the C compiler to go through than when unrolling it.

```c
for (cth_int var_i = 1; var_i < 10000; var_i += 1) {
    var_j = var_j + var_i;
}
```

```cth
for (Int i in [1, 8, 6, 11]) { # Comp-time ranges not fitting an arithmetic sequence must be allocated.
    j = j + i;
};
```

```c
// function scope:
cth_arr$4$cth_int val_a = {1, 8, 6, 11};
...
// local:
for (cth_int pos = 1; pos < 4; ++pos) {
    cth_int var_i = var_a[pos];
    var_j = var_j + var_i;
}
```

# Translating block expressions

```cth
Int [16] a;
Int [16] b = for (Int e in a) e * 2;
```

```c
// function:
cth_arr$16$cth_int val_a = {0};
cth_arr$16$cth_int val_f;
...
// local:
for (cth_int iter = 0; iter < 16; ++iter) {
    cth_int var_e = val_a[iter];
    val_f[iter] = var_e * 2;
}
cth_int * var_b = val_f;
```

```cth
Int [16] a;
Int [16] b;
Int [16] c = for (Int e in a, Int f in b) e * f * 2;
```

```c
// function:
cth_arr$16$cth_int val_a = {0};
cth_arr$16$cth_int val_b = {0};
cth_arr$16$cth_int val_f;
...
// local:
for (cth_int iter = 0; iter < 16; ++iter) {
    cth_int var_e = val_a[iter];
    cth_int var_f = val_b[iter];
    val_f[iter] = var_e * var_f * 2;
}
cth_int * var_b = val_f;
```

What about block expressions?

```cth
Int [16] a;
Int [16] b = for (Int e in a) {
    Int x = e + 2;
    return x * 2;
}
```

```c
// function:
cth_arr$16$cth_int val_a = {0};
cth_arr$16$cth_int val_f;
...
// local:
for (cth_int iter = 0; iter < 16; ++iter) {
    cth_int var_e = val_a[iter];

    __auto_type tuplevar_t = ({
        struct result { cth_int e0; } result;
        __label__ ret;

        ret: result;
    });

    val_f[iter] = var_e * 2;
}
cth_int * var_b = val_f;
```

What about arithmetic sequence ranges?

```cth
Int [16] a;
Int [16] b = for (Int e in a, Int i in [0 to 16]) e * i * 2;
```

```c
// function:
cth_arr$16$cth_int val_a = {0};
cth_arr$16$cth_int val_f;
...
// local:
for (
    struct {
        cth_int pos;
        cth_int var_i;
    } iter = {0, 1, 1};
    iter.pos < 16;
    ++iter.pos,
    iter.var_i += 1
) {
    cth_int var_e = val_a[iter];
    val_f[iter] = var_e * iter.var_i * 2;
}
cth_int * var_b = val_f;
```

## Translating conversion

```cth
# (Int a, Bool b)
(Float, Int) c = (Float, Int) (a, b);
```

```c
cth_float var_c0 = ((cth_float) var_a);
cth_int var_c1 = ((cth_int) var_b);
```
