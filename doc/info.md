# General info

## Documentation

There is no documentation currently. All files in this directory are my personal notes
and might contain outdated information.

## Compilation

Compile with `make`.

For compilation configuration, see `config.mk`.

To clean up, use `make clean`. This doesn't clean up the generated parser and lexer files.
To do so, use `make clean-gen`. This might mess up the makefile's included dependency files though.
I'll try to fix this as soon as possible, but until then, if this happens, comment out the last line of the makefile
(the one with an include), run `make`, stop it (it doesn't have to run till the end), then uncomment the last line, and run again.

## Tests

More thorough and maybe even automated tests will be added as soon as possible.
However, for now, these test files are more useful as just simple examples of the resulting Cynth code to concider.

Current test files mostly contain outdated examples. Semantics of the language are still evolving
to acommodate implementation and run-time complexity.
