# Tests

Various tests created during development will be located in the `tests/misc/` directory.
More specific code examples with comments will be located in the `tests/examples/` directory
to be used as a reference to understand some concepts and see them with compiler's feedback.

## Compiling tests

To compile the test files in `tests/`, run the following command:

```shell
make tests/out/{name}
```

Insert the name of the test file without the `.cth` extension
(possibly with a part of a path from `tests/misc/`) as `{name}`.
For example, the following command will compile the `tests/misc/001.cth` file
into the `tests/out/misc/001` executable.

```shell
make tests/misc/001
```

The compilation relies on a `gcc` compiler installed at the user's machine.
To specify a specific compiler name, change the `GCC` variable in `config.mk`.
However, note that the generated C code uses some GNU extensions,
so the compiler used must support the GNU dialect of C.

## Running tests

To run tests with no compilation, just to see the output C code, run the following command:

```shell
cat tests/{name}.cth | dist/compiler
```
