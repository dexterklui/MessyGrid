#!/usr/bin/env bash

echo -n "Test playing 2x2 grid...                                    "

cat $output_file > $tmp_file
head -n211 $tmp_file > $output_file
tail -n10 $tmp_file >> $output_file
