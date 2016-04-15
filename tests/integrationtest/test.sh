#!/bin/bash

#
# This is essentially just a crash test, not a proper unit test
#

gtestpass=0
gtestcount=0

EXEC=../../compiler

function itest() {
	gtestcount=$(($gtestcount+1))
	echo "Integration test: $1"
	cat $1 | $EXEC
	if [ $? -eq 0 ]; then
		gcc program.s ../../libs/* -o program
		./program
		if [ $? -eq 0 ]; then
			echo "Passed $1"
			gtestpass=$(($gtestpass+1))
		fi
	else
		echo "FAILED: compilation of $1"
		failedtests=$failedtests$1
	fi
}

itest "tests/arithmetic.src"
itest "tests/variables.src"
itest "tests/funccall.src"
itest "tests/funcdef.src"

printf "%d/%d tests passed\n" $gtestpass $gtestcount
