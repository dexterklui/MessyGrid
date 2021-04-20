#!/usr/bin/env bash

test_title="Play 2x2 grid and finish the game"

post_process() {
    cat $output_file > $tmp_file
    head -n211 $tmp_file > $output_file
    tail -n10 $tmp_file >> $output_file
}
