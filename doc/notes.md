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
