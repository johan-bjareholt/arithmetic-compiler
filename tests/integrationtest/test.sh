#!/bin/bash

#
# This is essentially just a crash test, not a proper unit test
#

testpass=0
testcount=0
failedtests=""

EXEC=../../compiler

function itest() {
	testcount=$(($testcount+1))
	echo "Integration test: $1"
	$EXEC $1
	if [ $? -eq 0 ]; then
		gcc program.s ../../libs/* -o program
		./program
		if [ $? -eq 0 ]; then
			echo "Passed: $1"
			testpass=$(($testpass+1))
		else
			echo "Test failed: $1"
			failedtests="$1, "
		fi
	else
		echo "FAILED: compilation of $1"
		failedtests="$1, "
	fi
}

itest "tests/arithmetic.src"
itest "tests/variables.src"
itest "tests/funccall.src"
itest "tests/funcdef.src"

printf "%d/%d tests passed\n" $testpass $testcount
printf "Failed tests: %s\n" $failedtests
