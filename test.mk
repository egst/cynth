foo = foo/bar.a bar/boo baz.c

.PHONY: test

x =
y =

test:
	echo '$(if $(x)$(y),foo,bar)'
