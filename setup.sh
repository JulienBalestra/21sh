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
    echo "Updating package source..."
    apt-get update -qq || brew update
    for package in python git valgrind libncurses5-dev
    do
        echo "Manage package named ${package}"
        apt-get install ${package} || brew install ${package}
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
    go_to_dirname
    path=$(pwd)
    packages
    setup_submodules
}

main
