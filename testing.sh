#!/bin/bash

PASS=0
FAIL=0

FOLDER=$1

for infile in "$FOLDER"/*.in; do
    base=$(basename "$infile" .in)
    outfile="$FOLDER/${base}.out"
    ./emulator $infile $outfile

    if diff -w -B -q "$FOLDER/${base}.myout" "$outfile" > /dev/null; then
        echo "$base : PASS"
        ((PASS++))
    else
        echo "$base : FAIL"
        ((FAIL++))
    fi
done

echo
echo "Passed: $PASS"
echo "Failed: $FAIL"