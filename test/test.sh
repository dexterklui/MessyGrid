#!/bin/bash

dir=$(echo $0 | sed -E 's+^(.*/)[^/]*$+\1+')
cd $dir || exit

echo "Running all existing unit tests..."

# Runs all unit test executables
executables=$(ls test_*.cpp | sed -E 's/.cpp$//')

for exe in $executables; do
    if [[ -x $exe ]]; then
        echo "=> $exe:"
        ./$exe
    fi
done
