#!/usr/bin/env bash

echo -n "Test start new game and exit in the middle...               "

cat $output_file > $tmp_file
grep '^Please input the number of rows (2-10):$' $tmp_file \
    | uniq > $output_file
grep '^Please input the number of columns (2-10):$' $tmp_file \
    | uniq >> $output_file
grep '^Please move the cell.$' $tmp_file | uniq >> $output_file
tail -n1 $tmp_file >> $output_file
