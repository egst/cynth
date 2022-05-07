# Semantic structures

This directory contains intermediate semantic structures to handle types, compile-time values
or other constructs such as declarations, or some compound structures like variables, typed expressions etc.

Everything here is located under the `cynth::sem` namespace.
Namespaces `cynth::sem::value` and `cynth::sem::type` group some of the structures.
Note that the same concept of a "category" with the `esl::category` representation as in `syn/`
also appears here, in `sem/`, but is not separated from other constructs.

There might be some complex circular dependencies. For explanation of some of the structure decisions, see `doc/deps.md`.
