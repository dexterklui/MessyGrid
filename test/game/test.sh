#!/usr/bin/env bash

# This is a script that provides a very primitive testing framework for testing
# a program's output. The framework runs the program with a prepared input and
# check the program's output (or processed output) against a prepared sample
#
# Usage: ./simpletest.sh [-v]
#
#        * With the flag -v / --verbose, it will show the difference between the
#          output and the sample output in case there is a mismatch (which can
#          only happen when there wasn't a timeout nor a runtime error during
#          program execution)
#
# Preparation:
#        This framework requires at least two files for each test case:
#        1) An input file whose content is fed to the program as input
#        2) A sample output file that contains the result to be checked against
#        3) [OPTIONAL] An executable script that defines:
#           1. A variable named "test_title" to store the title of the test case
#           2. A function name "post_process" to store any post-processing
#              scripts that has to run before comparing the output result.
#              This is useful because sometimes the program output is very long
#              or some part of it is random, so that you only want to extract
#              part of the output and check those parts.
#              See post_play_and_exit_2.sh and output_play_and_exit_2.txt for an
#              example.
#           3. A variable named "timeout" to specify the timeout duration for
#              this specfic test case. See the description of the variable
#              "default_timeout" below for how to specify the value
#              NOTE that you have to make that script executable to use it
#              (chmod u+x <script> to make it executable)
#
#        You can put the three files in three different directories respectively
#        or all in the same directory as long as you specify the directory path
#        below in the "Set variables" section.
#
#        The file names of the three test files consists of an optional prefix,
#        followed by a base name that must be the same for all three test files,
#        then end with an optional extension:
#        E.g. input/input_test_hello_1.txt
#             output/output_test_hello_1.txt
#             post/post_test_hello_1.sh
#        What the prefix and the extension are up to your choice as long as you
#        specify them below in the "Set variables" section
#
# Exit value:
#        0: all test passed
#        1: at least one test failed
#        2: main program (to be tested) not found or not executable
#        3: there were missing files for a test case
#        4: cannot cd into specified base directory

# Set variables
######################################################################
# Default timeout duration for each test. Units can be s, m, h, d, default is s.
# E.g. 0.03s. Set it to 0 to disable timeout. See timeout manpage for details.
default_timeout="0.05s"

# The maximum number of characters of the test case title to be printed.
# Characters beyond this limit are truncated away. You can change this value but
# don't exceed 80
max_title_len=50

# The directory where this script will cd into before running the test.
# The path given here is relative to the location where this script is in.
# So if you don't want to cd into anywhere, use "./" or "."
base_dir="../.."

# Please provide the paths relative to the base_dir of following files. For
# directories, you must use "." to indicate the same dir with base_dir. These
# paths are "exported" so you can use them in the script file of the test cases.
export prg="bin/main" # the program to be tested
export input_dir="test/game/input" # directory storing sample input files
export output_dir="test/game/output" # directory storing sample output files
export script_dir="test/game/post" # directory storing scripts of each test
export output_file="test/game/output.txt" # to store the output of the program (stdout)
export err_file="test/game/error.txt" # to store the error output of the program (stderr)
export tmp_file="test/game/tmp.txt" # not used, but you can use it in script

# Test files filename pattern (You can use an empty string)
export input_file_prefix="input_" # the prefix in sample input files' name
export output_file_prefix="output_" # the prefix in sample output files' name
export script_file_prefix="post_" # the prefix in script files' name
export input_file_suffix=".txt" # the suffix in sample input files' name
export output_file_suffix=".txt" # the suffix in sample output files' name
export script_file_suffix=".sh" # the suffix in script files' name


# You should not need to change the values of the following variables.
# escape sequences to change the text style of echo -e message
RED='\033[31;1m' # red and bold
GRN='\033[32;1m' # green and bold
BLE='\033[34m' # blue
NRM='\033[0m' # normal: reset the style
BLD='\033[1m' # bold
HUNDRED_SPACES="                                                                                "

num_test=0 # count total number of tests
num_fail=0 # count total number of failed tests

# Begin the test from here
######################################################################
echo -e "${BLD}--- Start simple testing ---${NRM}"

# cd into base directory. Exit if fail
dir="$(echo "$0" | sed 's-\(^.*\)/[^/]\+$-\1-')/$base_dir"
cd "$dir"
if [[ ! $? -eq 0 ]]; then
    echo -e "Could not cd into ${BLD}$dir${NRM}!"
    exit 4
fi

# check if the main program to be tested exists and is executable
if [[ ! -x $prg ]]; then
    echo -e "${RED}Main program $prg not found or not executable!${NRM}"
    exit 2
fi

echo -e "${BLD}Program to be tested: ${NRM}$prg" # echo the program name

# Find all input files
input_files=$(ls $input_dir/$input_file_prefix*$input_file_suffix)

# Escape the . for RegEx
input_file_suffix=$(echo "$input_file_suffix" | sed 's/\./\\./g')
output_file_suffix=$(echo "$output_file_suffix" | sed 's/\./\\./g')
script_file_suffix=$(echo "$script_file_suffix" | sed 's/\./\\./g')
input_dir=$(echo "$input_dir" | sed 's/\./\\./g')
output_dir=$(echo "$output_dir" | sed 's/\./\\./g')
script_dir=$(echo "$script_dir" | sed 's/\./\\./g')

# loop all test cases (for each prepared input file)
for input_file in $input_files; do
    # set the name of sample output file and script file for this test case
    sample_output=$(echo $input_file | \
        sed "s+$input_dir/+$output_dir/+" | \
        sed "s+/$input_file_prefix+/$output_file_prefix+" | \
        sed "s+$input_file_suffix\$+$output_file_suffix+")
    post_script=$(echo $input_file | \
        sed "s+$input_dir/+$script_dir/+" | \
        sed "s+/$input_file_prefix+/$script_file_prefix+" | \
        sed "s+$input_file_suffix\$+$script_file_suffix+")

    # check if corresponding sample output file and script file is present
    if [[ ! -r $sample_output ]]; then
        echo -e "${RED}$sample_output not found or not readable!${NRM}"
        exit 3
    fi

    # reset or update variables and functions
    num_test=$(($num_test + 1)) # increment number of test case by 1
    test_exit_value=-1 # store the exit value of running the current test case
    diff_exit_value=-1 # store the exit value of running diff (compare output)
    # default title is the filename without the prefix and suffix
    test_title=$(echo $input_file | \
        sed "s+$input_dir/+/+" | \
        sed "s+/$input_file_prefix++" | \
        sed "s+$input_file_suffix\$++")
    post_process() { :; } # reset the post_process function to do nothing
    timeout=$default_timeout # reset the timeout duraction to default

    # Run the script of this test case to define the title and post-process
    # function, and optionally change the timeout duration
    if [[ -x $post_script ]]; then
        . $post_script
    fi

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
    timeout ${timeout} ./$prg < $input_file > $output_file 2> $err_file
    test_exit_value=$?

    # if there wasn't any runtime error or timeout, post-process the program
    # output, and then compare it against the sample output
    if [[ $test_exit_value -eq 0 ]]; then
        post_process
        diff $output_file $sample_output > $err_file
        diff_exit_value=$?
    fi

    # echo the result of this test case
    if [[ $diff_exit_value -eq 0 ]]; then
        echo -e "[ ${GRN}OK${NRM} ]"
    else
        num_fail=$(($num_fail + 1))
        echo -e "[ ${RED}FAIL${NRM} ]"

        if [[ $test_exit_value -eq 0 ]]; then
            echo "Output does not match desired result"
            if [[ $1 == "-v" || $1 == "--verbose" ]]; then
                echo "diff $output_file $sample_output"
                cat $err_file
            fi
        elif [[ $test_exit_value -eq 124 ]]; then
            echo "Test case timeout."
            if [[ -s $err_file ]]; then # if there is error message
                echo -n "Error messages "
                echo "prepended with the number of consecutive occurences:"
                cat $err_file | uniq -c # prevent repeating msg flooding screen
            fi
        else
            echo -e "Encountered error with exit code $RED$test_exit_value$NRM."
            if [[ -s $err_file ]]; then # if there is error message
                echo "Error messages:"
                cat $err_file
            fi
        fi

        echo -e "=> Test case input file: ${BLE}$input_file${NRM}"
    fi
done

# clean up temporary files
rm -f $output_file $err_file $tmp_file

# echo the summary
echo
if [[ $num_fail -eq 0 ]]; then # no test failed
    echo -e "${BLD}Game testing: ${GRN}All $num_test tests passed.${NRM}"
else # at least 1 test failed
    echo -ne "${BLD}Game testing: "
    echo -e "${RED}$num_fail of $num_test tests failed.${NRM}"
    exit 1
fi
