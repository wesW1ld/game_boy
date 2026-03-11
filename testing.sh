#!/bin/bash

PASS=0
TOTAL=1

FOLDER=$1

for infile in "$FOLDER"/*.in; do
    base=$(basename "$infile" .in)
    outfile="$FOLDER/${base}.out"
    ./emulator $infile $outfile

    if diff -w -q "$FOLDER/${base}.myout" "$outfile" > /dev/null; then
        PASS=$(($PASS + 1))
    fi
done

echo $PASS cases passed out of $TOTAL