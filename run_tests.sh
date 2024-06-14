#!/bin/bash

# Check if correct number of arguments is given
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory> <program>"
    exit 1
fi

# Assign arguments to variables
DIRECTORY=$1
PROGRAM=$2

# Check if the directory exists
if [ ! -d "$DIRECTORY" ]; then
    echo "Error: Directory $DIRECTORY does not exist."
    exit 1
fi

# Check if the program exists and is executable
if [ ! -x "$PROGRAM" ]; then
    echo "Error: Program $PROGRAM does not exist or is not executable."
    exit 1
fi

# Iterate over each file in the directory
for INPUT_FILE in "$DIRECTORY"/*.in.txt; do
    if [ -f "$INPUT_FILE" ]; then
        OUTPUT_FILE="${INPUT_FILE/.in.txt/.res.txt}"
        echo "Processing file: $(basename ${INPUT_FILE})"
        "$PROGRAM" <"$INPUT_FILE" >"$OUTPUT_FILE"
    fi
done
