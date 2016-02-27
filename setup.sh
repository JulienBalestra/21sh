#!/bin/bash

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

function packages
{
    valgrind --version
    if [ $? -eq 0 ]
    then
        echo "valgrind already setup"
        return 0
    fi
    echo "Updating package source..."
    apt-get update -qq || brew update > /dev/null
    for package in valgrind libncurses5-dev
    do
        echo "Installing package named ${package}"
        apt-get install ${package} -qqy > /dev/null || brew install ${package} > /dev/null
        which ${package}
    done
}

function setup_submodules
{
    echo "Setup git submodules..."
    for module in libft
    do
        git submodule init ${module}
        git submodule update --remote ${module} || git submodule update ${module}
    done
}

function main
{
    uname -a
    # Requirements
    go_to_dirname
    path=$(pwd)
    setup_submodules
    packages
    return $?
}

main
exit $?
