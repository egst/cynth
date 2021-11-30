## Compilation

Compile with `make`.

To clean up, use `make clean`. This doesn't clean up the generated parser and lexer files.
To do so, use `make clean-gen`. This might mess up the makefile's included dependency files though.
This will be fixed as soon as possible, but until then, if this happens, comment out the last line of the makefile
(the one with an include), run `make`, stop it (it doesn't have to run till the end), then uncomment the last line, and run again.

## Tests

More thorough and maybe even automated tests will be added as soon as possible.
However, for now, these test files are more useful as just simple examples of the resulting Cynth code to concider.

The tests starting with `test0` is the first series of tests that were created during the initial development.
They are a little chaotic and also might be outdated in some expected behaviour.

The tests starting with `testA` are currently relevant and all notes and comments
and the tested features themselves in there are up to date.

The tests starting with `testX` are just some additional experiments.
