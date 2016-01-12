#!/bin/bash

BIN=minishell
TEST=test_minishell
LIB=libsh.a

set -x

function go_to_dirname
{
    echo "Go to working directory..."
    cd $( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
    if [ $? -ne 0 ]
    then
        echo "go_to_dirname failed";
        exit 1
    fi
    echo "-> Current directory is" $(pwd)
}

function makefile_rules
{
    make fclean
    make
    original=$(ls -l ./.objects/)
    sleep 61
    make
    no_link=$(ls -l ./.objects/)
    if [ "${original}" != "${no_link}" ]
    then
        echo "fail rules: make ; make"
        exit 1
    fi
    make re
    re_link=$(ls -l ./.objects/)
    if [ "${original}" != "${no_link}" ]
    then
        echo "fail rule: make re"
        exit 1
    fi
    make clean
    if [ -d ./.objects/ ]
    then
        echo "fail rule: make clean"
        exit 1
    fi
    if [ ! -f ${BIN} ]
    then
        echo "fail rule: make clean"
        exit 1
    fi
    if [ ! -f ${LIB} ]
    then
        echo "fail rule: make clean"
        exit 1
    fi
    make fclean
    if [ -f ${BIN} ]
    then
        echo "fail rule: make clean"
        exit 1
    fi
    if [ -f ${LIB} ]
    then
        echo "fail rule: make clean"
        exit 1
    fi
    if [ -f ${TEST} ]
    then
        echo "fail rule: make test already here"
        exit 1
    fi
    make test
    if [ ! -f ${TEST} ]
    then
        echo "fail rule: make test not here"
        exit 1
    fi
}

function main
{
    go_to_dirname
    makefile_rules

}

main
exit $?