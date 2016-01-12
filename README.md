# Minishell


[![Build Status](https://travis-ci.org/JulienBalestra/21sh.svg?branch=master)](https://travis-ci.org/JulienBalestra/21sh)


Recode of a /bin/bash like

# How to launch


	./setup.sh
	make
	./minishell


# Which features are done

* AST recurse basic parsing and exec
* |
* >
* >>
* <

# How to test

The following command will install valgrind for leaks and errors utilities (and gdb).

	./setup.sh && ./run_test.sh