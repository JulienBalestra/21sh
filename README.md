# Minishell


[![Build Status](https://travis-ci.org/JulienBalestra/21sh.svg?branch=master)](https://travis-ci.org/JulienBalestra/21sh)
[![Circle CI](https://circleci.com/gh/JulienBalestra/21sh.svg?style=svg)](https://circleci.com/gh/JulienBalestra/21sh)

Recode of a /bin/bash like

# How to launch with sudo needed


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

	./setup.sh && ./run_test.sh # include make rules testing