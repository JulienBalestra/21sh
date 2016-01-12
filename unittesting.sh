#!/bin/bash

BIN=./test_minishell
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

function compilation
{
    if [ -f ${BIN} ]
    then
        rm ${BIN}
    fi
    make test
}

function main
{
    go_to_dirname
    compilation
    ${BIN}
}

main
exit $?