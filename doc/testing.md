# Tests

Various test inputs created during development are located in the `tests/in/misc/` directory.
More specific code examples with comments will be located in the `tests/in/examples/` directory
to be used as a reference to understand some concepts and see them with compiler's feedback.

In general, test inputs (Cynth code files) are located in `tests/in/`, while the intended test outputs location is `tests/out/`.
The outputs can be generated automatically with the provided makefile.
Output C code files are located in `tests/out/c/`. Binary outpur files are located in `tests/out/bin/`
and are separated into standalone executables for debugging purposes in `tests/out/bin/debug/`,
object files for linkage with the control program `tests/out/bin/synth/` and
final executable programs (the control program linked with one of the synth programs) in `tests/out/bin/complete/`.

## Compiling tests

To compile the test files in `tests/`, run one of the following commands:

```shell
make tests/out/c/{name}
make tests/out/bin/debug/{name}
make tests/out/bin/synth/{name}
make tests/out/bin/complete/{name}
```

In place of `{name}`, insert the name of the test file 
(possibly with a part of a path relative to `tests/in/`)
with the appropriate output extention.

For example, the following command will compile the input `tests/in/misc/001.cth` Cynth code file
into the output `tests/out/bin/debug/misc/001` standalone executable.
*Use the appropriate executable extention for your system, e.g. `001.exe` on Windows.*

```shell
make tests/out/bin/debug/misc/001
```

This one will compile `tests/in/misc/001.cth` into the output `tests/out/c/misc/001` C code file.

```shell
make tests/out/c/misc/001.c
```

The compilation of the intermediate C files relies on a `gcc` compiler installed at the user's machine.
To specify a specific compiler name, change the `GCC` variable in `config.mk`.
However, note that the generated C code uses some GNU extensions,
so the compiler used must support the GNU dialect of C.
