# Categories & Nodes Circular Dependecy Structure Solution

All tree structures (AST and other semantics related structures)
are implemented with categories (variants - for polymorphism) and components (pointers - for recursion).

```c++
//[file: syn/categories/forward.hpp]
#pragma once
namespace cynth::syn::category {
    struct ArrayElement;
    struct Expression;
    //...
}
```

Nodes contain components (`esl::component` and other variations) of categories (or sometimes nodes or other values directly).
`component<T>` is essentially `T *` (with additional cleanup logic)
so a node defined with components of incomplete types it a complete type.

```c++
//[file: syn/nodes/incomplete/expressions.hpp]
#pragma once
#include "syn/categories/forward.hpp"
namespace cynth::syn::node {
    struct Add {
        component<category::Expression> left;
        component<category::Expression> right;
    };
    struct Subscript {
        component<category::Expression> container;
        component_vector<category::ArrayElement> location;
    };
    //...
}
```

Categories contain variants (`std::variant`) of nodes.
`variant<T, U>` is essentially `union { T; U; }` (with additional type checking logic)
so it needs its underlying types to be complete. Forward declaration of a node won't do.

```c++
//[file: syn/categories/incomplete/expression.hpp]
#pragma once
#include "syn/nodes/incomplete/expressions.hpp"
namespace cynth::syn::category {
    struct Expression {
        variant<
            node::Add,
            node::Subscript,
            //...
        > value;
    };
}
```

Upon inclusion of `nodes/forward/*.hpp` and `categories/forward/*.hpp`, all of the structures above are complete types.
However, the child nodes refered to by components might be incomplete and cannot be used in any direct operation.
For this reason, additional headers are created, that include the component-refered dependencies as complete types.

```c++
//[file: syn/nodes/expressions.hpp]
#pragma once
#include "syn/nodes/forward/expressions.hpp"
#include "syn/categories/incomplete/array_element.hpp"
#include "syn/categories/incomplete/expression.hpp"
```

```c++
//[file: syn/categories/expression.hpp]
#pragma once
#include "syn/categories/forward/expression.hpp"
#include "syn/nodes/expression.hpp"
```
