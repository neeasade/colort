#!/usr/bin/env bash
# test script for args and output
# needs bash 4+ for associative arrays.

# target program to test
target=./colort
which >/dev/null $target || exit 1

# args, expected output
declare -A tests=(
	["1 #000000"]="#010101"
	["-l 1 #FFFFFF"]="#FFFFFF"
	["-i #000000"]="#FFFFFF"
	["60 #000000"]="#3C3C3C"
	["-60 #000000"]="#C4C4C4"
	["-s 4 1 spam000000spam"]="spam010101spam"
	["-t -s 4 1 spam000000spam"]="010101"
	["-r 1 000000"]="010000"
	["-t #ff000000"]="000000"
	["-t 3CCCCC"]="3CCCCC"
)

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
