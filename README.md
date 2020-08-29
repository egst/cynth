# How do I compile the stuff?

I work in WSL - linux subsystem under windows.
Compiling the compiler and lexer with bison and flex is done in the Linux environment with:

```sh
run/gen
```

The final executable is then built with clang in the Windows environment with:

```ps
run/com
```

The executable is then located in the `bin/` directory:

```ps
bin/parser test
```
