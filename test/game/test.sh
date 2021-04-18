#!/usr/bin/env bash

# This is a script that provides a very primitive automation for testing the
# game by feeding in input and checking against the output.
#
# Usage: It requires three files for each test case:
#        1) An input file whose content is passed to the program as input
#        2) An output file that prepares the result to be checked against
#        3) An executable bash script that echos the test case name and does any
#           post-processing if needed (e.g. post-processing the output of the
#           program before checking them against the content of the output file)
#
#        Put the three files in three corresponding directories respectively:
#        input/, output/ and post/.
#        The file names of the three files consist of a corresponding prefix
#        followed by a custom name, then end with a corresponding file
#        extension:
#        E.g. input/input_test_hello_1.txt
#             output/output_test_hello_1.txt
#             post/post_test_hello_1.sh
#        Make sure the executable bash script (in post/) is executable.
#
#        There is a timeout duration for each test case, exceeding it will
#        result as a failure for that test case. You can change the timeout
#        duration in thie file below.

# set timeout duration for each test
timeout=0.05

export prg="bin/main"
export test_dir="test/game"
export input_dir="$test_dir/input" # storing the input of each tests
# store the result to be checked against for each test
export output_dir="$test_dir/output"
# store post script that echo the title of this test and post process the output
# before checking it agsint the sameple output (because sometimes we don't want
# to check the whole output but only a part of it)
export post_script_dir="$test_dir/post"

export output_file="$test_dir/output.txt" # to store the output
# as an intermediate file for post processing of the output file
export tmp_file="$test_dir/tmp.txt"

failed=0 # as a temporary variable to store the result of each test
num_test=0 # count total number of tests
num_fail=0 # count total number of failed tests


# Being the test
######################################################################
echo "### Testing the game as a whole ###"

if [[ ! -x $prg ]]; then
    echo "Main program $prg not executable!"
    exit 2
fi


for input_file in $(ls $input_dir/input_*.txt); do
    num_test=$(($num_test + 1))
    sample_output=$(echo $input_file | \
        sed 's+input/+output/+' | sed 's+/input_+/output_+')
    post_script=$(echo $input_file | \
        sed 's+input/+post/+' | sed 's+/input_+/post_+' | sed 's+txt$+sh+')

    if [[ ! -f $sample_output || ! -x $post_script ]]; then
        echo "$sample_output or $post_script not found!"
        exit 3
    fi

    timeout ${timeout}s $prg < $input_file > $output_file
    if [[ ! $? -eq 0 ]]; then failed=1; fi

    $post_script
    diff $output_file $sample_output > /dev/null
    if [[ ! $? -eq 0 ]]; then failed=1; fi

    if [[ ! $failed -eq 0 ]]; then
        num_fail=$(($num_fail + 1))
        echo "[FAIL]"
        echo -n "    Input file using: $input_file"
    fi

    failed=0
    echo
done

# clean up temporary files
rm $output_file $tmp_file

echo
echo "$num_fail of $num_test tests have failed."
test ! $num_fail -eq 0 && exit 1 || exit 0
