# Coding style conventions

I follow many different conventions, some of them implicitly without really specifying it.
I will specify them all once this project reaches the potential for collaboration with other people,
but for now, the following list of conventions are just some explicit coding style notes for me,
to keep consistent and stop changing my style during development.

* semantic order of parameters:
    * source, then destination (`copy(src, dst)`, `assign(value, target)`, ...)

* comments: currently not standardized, but:
    * `/** (*  ...) */` is used to comment interfaces with examples and explanations for the user (caller)
        (some IDE tools pick those up as docblocks. clangd seems to be picking up any comment above a declaration)
    * `/*** (...) ***/` is used for examples of input Cynth code or output C code
        (because it sortof resembles the tripple backslash code blocks in markdown)
        placed in some parts of the implementation for demonstration
    * `#` is used in Cynth code (though it does support both `//` and `#`)
    * but other than that, the inconcictency of comments hasn't triggered my OCD yet, so I don't really care (for now)

* header files should not (in general) have incomplete dependencies in type declarations (not even in pointers)  
    in case that types really cannot be complete (e.g. circular dependencies):  
    * files with incomplete circular dependencies should be explicitly marked as such (placed in a directory `incomplete/` or prefixed with `incomplete_`)
    * additional file with full declarations of the circular dependencies should be provided
    update: what about types in declared (to be defined in an implementation file) function signatures?
    (e.g. `context/forward`, `interface/forward`)
    I guess I'll allow that for now and see if it introduces any maintanance issues

* in functions, prefer explicit return type with generic initializer return over auto return type with explicit initializer return  
    i.e. `-> result` and `return {value}` instead of `-> auto` and `return result{value}`  
    explicit specification of output types instead of auto just feels more selfdocumenting
    and avoids the need to specify the type on every return  
* `detail` namespaces began to collide. specify them locally as e.g. `detail::lift`, `detail::iterator` etc.  
    right now, I'm using the file name in `detail::{filename}` and I'll probably stick with it
* keeping track of noexcept could be nice i guess

* specify namespaces explicitly, except for:
    * the top-level `cynth::` namespace
    * the `sem::` and `syn::` namespaces
    * `detail::*` namespaces
    * when refering to a struct inside its declaration
* in esl implementation as well as in code refering to it, also specify the top-level `esl::` namespace  
    same goes for `std::` and potentially other libraries
    esl uses the `standard_case` naming convention

* `PascalCase` for types (structs, classes, typedefs)  
    a common practice in most style guides  
    helps distinguish types and values visually even without any IDE help  
    eliminates the need to come up with clever descriptive names every time when even e.g. `Vector vector` is enough  
    not that it isn't a good practice to name variables more descriptively than `vector` or `result`
    but often, especially in generic code, it won't get more specific tahn just `vector`
* `camelCase` for values (variables and members, incl. constants and enum values) and functions (incl. all methods)
    other style guides commonly use `camelCase`, `snake_case` or `PascalCase`  
    I'd like to reserve `PascalCase` for types only but I don't really care if it's `snake_case` or `camelCase`
    `camelCase` just feels more fitting with `PascalCase` types though
    some style guides distinguish between variables, members, functions and methods  
    I don't want to do that because `a)` even a variable might refer to a function and `b)`
    I want to keep the naming rules simple - I don't really want to mix `snake_case` and `camelCase`/`PascalCase`  
* `camelCase` for concepts  
    they're basically templated boolean values that may also appear in some special locations
* `ALL_CAPS` macros (and macros only)  
    I really want to avoid macros at all costs except for:
    * debug tools for use in development only  
      `esl` provides such macros with an explicit opt-in header `esl/macros.hpp`
    * local macros (`#define`d after any `#include`s and `#undef`ined at the end of a file) for repetitive interfaces  
      hopefully, this will be solved with generative programming tools in C++23, but until then this is the best I can do
* `snake_case` for namespaces  
    distinguishing between types and namespaces allows having a type and a namespace with related constructs
    When those constructs cannot be nested in the type e.g. `struct type::Complete` and `struct type::complete::Int`  
    I didn't want to mix `snake_case` and `camelCase` but most major style guides use `snake_case` for namespaces
    so I'll stay consistent with them
* exception: `snake_case` (aka `standard_case`) to conform with or mimic `std::` related stuff - everyhting in `esl::`  
    also, PascalCase type tpl parameter and ALL_CAPS non-type tpl parameters everywhere in `esl::`  
    otherwise, there is no reason to differentiate tpl parameters and other values and types
* avoid hungarian notation  
    except maybe for some short lived values where it might help with quick orientation
    in a complex algorithm with a bunch of helper wrappers and pointers to "unpack" e.g. `nodePtr`, `evalResult` etc.
* `detail::foo` namespacpace for implementation helpers in a file (or some sort of semantic section) named `foo`  
    don't use plain `detail` namespace, as the names could quickly start to collide
* `f()` everywhere, except `f ()` in declarations/definitions  
    same goes for `t<>` and `t <>`  
    `a[]` everywhere
* `requires ()` with explicit parentheses
* `CTH_` (and `ESL_`) prefix for non-local macros and `cth_` prefix for global C code
* avoid creating unnecessary abbreviations and acronyms  
    where abbreviations are ok:
    * `syn::node::*` (e.g. `syn::node::Gt`, `syn::node::ExprIf`, `syn::node::TypeDef`)
