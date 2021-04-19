#!/usr/bin/env bash

test_title="Start new game, input invalid command, then exit"

post_process() {
    cat $output_file > $tmp_file
    grep '^Please input the number of rows (2-10):$' $tmp_file \
        | uniq > $output_file
    grep '^Please input the number of columns (2-10):$' $tmp_file \
        | uniq >> $output_file
    grep '^Please move a piece:$' $tmp_file | uniq >> $output_file
    tail -n1 $tmp_file >> $output_file
}
