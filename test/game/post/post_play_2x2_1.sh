#!/usr/bin/env bash

test_title="Play 2x2 grid and finish the game"

post_process() {
    cat $output_file > $tmp_file
    head -n210 $tmp_file > $output_file
    tail -n9 $tmp_file >> $output_file
}
