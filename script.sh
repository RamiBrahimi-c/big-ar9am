#!/bin/bash



prgrm=$1
file_name=$2

passed=0
failed=0

NUMBER_OF_TESTS=1000


standard_path="./tests/output/bin/"
test_c_prgrm_name="run_tests_main"
test_python_prgrm_name="./tests/main.py"
full_c_path="$standard_path$test_c_prgrm_name"

full_py_path="$test_python_prgrm_name"
python_interpreter="python3"

operation=" sub "
# echo $full_path
pwd
for ((i=0; i<$NUMBER_OF_TESTS; i++)) do
    NUM1=$(( (SRANDOM  ) + 4))
    NUM2=$(( (SRANDOM % (NUM1 / 200 + 1)) + 2 ))

    echo "================ test Number: $i =============================="
    echo "num1: $NUM1"
    echo "num2: $NUM2"
    numbers="$NUM1 $NUM2"
    full_c_test_line="$full_c_path$operation$numbers"
    full_py_test_line="$full_py_path$operation$numbers"
    # result_one=$("$full_test_line")
    result_in_c=$("$full_c_path" $operation "$NUM1" "$NUM2")
    result_in_py=$(python3 "$full_py_path" $operation "$NUM1" "$NUM2")
    
    # echo "$full_py_test_line"
    # echo "$full_py_path"
    # echo "$full_c_test_line"
    # echo "$full_c_path"
    echo "$result_in_c"
    echo "$result_in_py"

    if [[ "$result_in_c" == "$result_in_py" ]]; then
        echo "✅ The strings match."  # trust me this is not AI i brought the emoji from https://emojipedia.org/check-mark-button
        ((passed++))
    else
        echo "❌ The strings do not match." # same here twin https://emojipedia.org/cross-mark
        ((failed++))
        exit 1
    fi    
    echo "==============================================================="
done

echo "==============================================================="
echo "|| Total tests : $NUMBER_OF_TESTS                  "
echo "|| ✅ passed tests : $passed                          "
echo "|| ❌ failed tests : $failed                          "
echo "==============================================================="

# set -xe
