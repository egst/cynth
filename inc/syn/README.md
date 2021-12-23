# AST nodes

This directory contains representation of the AST.

Everything here is located in the `cynth::syn` namespace. All AST structures are separated
into "categories" (in `cynth::syn::category` namespace and `syn/categories/` directory)
and "nodes" (in `cynth::syn::node` namespace and `inc/syn/nodes/` directory).
Nodes represent the AST nodes while categories only group some of these nodes
(for tighter type representation and less alternatives to go through in variants).
Note that semantic structures (`sem/`) also contain "categories" of structures
with the same representation (`esl::category`), but they are not that well separated in there.

There might be some complex circular dependencies. For explanation of some of the structure decisions, see `doc/deps.md`.
