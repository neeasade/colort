#!/usr/bin/env bash
# test script for args and output
# needs bash 4+ for associative arrays.

declare -A tests

# target program to test
target=./colort

# args, expected output
tests=(
	["1 #000000"]="#010101"
	["-l 1 #FFFFFF"]="#FFFFFF"
	["-i #000000"]="#FFFFFF"
	["60 #000000"]="#3C3C3C"
	["-60 #000000"]="#C4C4C4"
	["-s 4 1 spam000000spam"]="spam010101spam"
	["-t -s 4 1 spam000000spam"]="010101"
	["-r 1 000000"]="010000"
)

# sanity
if ! which $target; then
	echo "$target was not found."
	exit 1
fi

# do the thing
for testCase in "${!tests[@]}"; do
	result="`$target $testCase`"
	expected="${tests["$testCase"]}"

	if [[ "$result" = "$expected" ]]; then
		echo -n .
	else
		echo "Test Failed: $target $testCase"
		echo "Expected: $expected"
		echo "Result  : $result"
	fi
done

echo "All done."
