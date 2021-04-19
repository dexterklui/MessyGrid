#!/usr/bin/env bash

# This is a script that provides a very primitive automation for testing the
# game by feeding in input and checking against the output.
#
# Usage: It requires three files for each test case:
#        1) An input file whose content is passed to the program as input
#        2) An output file that prepares the result to be checked against
#        3) An executable bash script that defines a variable and a function:
#           1. A variable named test_title to store the test title.
#           2. A function name post_process() to store any post-processing
#              scripts that has to run before checking the output result.
#              If no post-processing is needed, use post_process() { :; }
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
#
# Exit value: 0: all test passed
#             1: at least one test failed
#             2: main program (to be tested) not found or not executable
#             3: there were missing files for a test case

# Set variables
######################################################################
timeout=0.05 # timeout duration for each test (float with the unit second)
max_title_len=50 # the maximum length of the title to be printed (don't > 100)

export prg="bin/main" # programe path
export test_dir="test/game" # game testing directory
export input_dir="$test_dir/input" # directory storing sample input
export output_dir="$test_dir/output" # directory storing sample output
export script_dir="$test_dir/post" # directory storing scripts of each test
export output_file="$test_dir/output.txt" # to store the output of each test
export tmp_file="$test_dir/tmp.txt" # tmp file for storing error and processing

# escape sequences to change the style of echo -e message
export RED='\033[31;1m' # red
export GRN='\033[32;1m' # green
export NRM='\033[0m' # normal: reset the style
export BLD='\033[1m' # bold
HUNDRED_SPACES="                                                                                                    "

fail_type=0 # as a temporary variable to store the result of each test
num_test=0 # count total number of tests
num_fail=0 # count total number of failed tests

# Begin the test
######################################################################
echo -e "${BLD}--- Start game testing ---${NRM}"

# check if main program to be tested exists and is executable
if [[ ! -x $prg ]]; then
    echo -e "${RED}Main program $prg not executable!${NRM}"
    exit 2
fi

# loop all test case (for each prepared input file)
for input_file in $(ls $input_dir/input_*.txt); do
    # set the name of sample output file and script file for this test case
    sample_output=$(echo $input_file | \
        sed 's+input/+output/+' | sed 's+/input_+/output_+')
    post_script=$(echo $input_file | \
        sed 's+input/+post/+' | sed 's+/input_+/post_+' | sed 's+txt$+sh+')

    # check if corresponding sample output file and script file is present
    if [[ ! -f $sample_output || ! -x $post_script ]]; then
        echo -e "${RED}$sample_output or $post_script not found!${NRM}"
        exit 3
    fi

    # increment number of test run by 1
    num_test=$(($num_test + 1))

    # Run script of this test case to define the title and post-process function
    . $post_script

    # echo the title of this test case
    title_length=$(echo "$test_title" | wc -c)
    if [[ $title_length -gt $max_title_len ]]; then
        test_title=$(echo "$test_title" | grep -o "^.\\{${max_title_len}\\}")
        space=""
    else
        space_length=$(($max_title_len - $title_length + 1))
        space=$(echo "$HUNDRED_SPACES" | grep -o "^ \\{${space_length}\\}")
    fi
    echo -ne "${BLD}TEST ${test_title}...${space}${NRM}"

    # Set a timeout duration and run the program with prepared input
    timeout ${timeout}s $prg < $input_file > $output_file 2> $tmp_file
    if [[ ! $? -eq 0 ]]; then fail_type=1; fi

    # post-process and compare outputs, if there wasn't error or timeout
    if [[ $fail_type -eq 0 ]]; then
        post_process
        diff $output_file $sample_output > /dev/null
        if [[ ! $? -eq 0 ]]; then fail_type=2; fi
    fi

    # echo test result
    if [[ $fail_type -eq 0 ]]; then
        echo -ne "[ ${GRN}OK${NRM} ]"
    else
        num_fail=$(($num_fail + 1))
        echo -e "[ ${RED}FAIL${NRM} ]"

        if [[ $fail_type -eq 1 ]]; then
            echo "Error during test or timeout. Error message (if any):"
            test -s $tmp_file && cat $tmp_file
        elif [[ $fail_type -eq 2 ]]; then
            echo "Output does not match desired result"
        fi

        echo -n "Input file of this test: $input_file"
    fi
    echo

    fail_type=0 # reset fail_type to 0 for next test case
done

# clean up temporary files
rm -f $output_file $tmp_file

echo
if [[ $num_fail -eq 0 ]]; then
    echo -e "${BLD}Game testing: ${GRN}All tests passed.${NRM}"
else
    echo -ne "${BLD}Game testing: "
    echo -e "${RED}$num_fail of $num_test tests have failed.${NRM}"
    exit 1
fi
