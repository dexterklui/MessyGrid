#!/bin/bash

cd test/ || exit
echo "Running all existing unit tests..."

# Runs all unit test executables
executables=$(ls *.cpp | grep '^test_.*\.cpp' | sed -E 's/.cpp$//')

for exe in $executables; do
    if [[ -x $exe ]]; then
        echo "$exe:"
        ./$exe
    fi
done
