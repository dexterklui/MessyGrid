#!/usr/bin/env bash

test_title="Test start new game, invalid cmd then exit game...          "

post_process() {
    cat $output_file > $tmp_file
    grep '^Please input the number of rows (2-10):$' $tmp_file \
        | uniq > $output_file
    grep '^Please input the number of columns (2-10):$' $tmp_file \
        | uniq >> $output_file
    grep '^Please move the cell.$' $tmp_file | uniq >> $output_file
    tail -n1 $tmp_file >> $output_file
}
