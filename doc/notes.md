# Misc. notes on translation

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

Note that the examples above don't account for passing a structure of runtime captured values
or any conditional function selection.

# Translating tuple expressions

All built-in operators return the same kind of tuple as their arguments.
The translation of these happens "in paralel" - the individual tuple elements are processed separately with
the other corresponding arguments (e.g. `(1, 2) + (2, 3)` performs `1 + 2` and `2 + 3` separately).
So these can be simply translated into separate C expressions and variables.

On the other hand, functions, expression blocks and expression if..else conditions might result in a tuple of any size.
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

# Translating functions

```c
// Static:
struct cth_ret_f  { ... };
struct cth_ctx_f0 { ... };
struct cth_ctx_f1 { ... };
struct cth_ctx_f2 { ... };
struct cth_ctx_f  {
    int branch;
    union {
        cth_ctx_f0 e0;
        cth_ctx_f1 e1;
        cth_ctx_f2 e2;
    } data;
};
cth_ret_f cth_fsw_f0 (cth_ctx_f0 const * ctx, ...) { ... }
cth_ret_f cth_fsw_f1 (cth_ctx_f1 const * ctx, ...) { ... }
cth_ret_f cth_fsw_f2 (cth_ctx_f2 const * ctx, ...) { ... }
cth_ret_f cth_fsw_f  (cth_ctx_f  const * ctx, ...) {
    switch (ctx.branch) {
    case 0:
        return cth_ctx_f0(ctx.data.e0, ...);
    case 1:
        return cth_ctx_f1(ctx.data.e1, ...);
    case 2: default: // Default should indcate an implementation error, but let's keep it here for now.
        return cth_ctx_f2(ctx.data.e2, ...);
    }
}

// Local:
__auto_type var_t = ({
    struct result {
        cth_int e0;
        cth_int e1;
    };
    struct result result;
    __label__ ret;

    ...

    if (x)
        result.e0 = (struct cth_ctx_f) {0, {...}};
    if (y)
        result.e0 = (struct cth_ctx_f) {1, {...}};
    result.e0 = (struct cth_ctx_f) {2, {...}};

    ...

    ret:
})
```
