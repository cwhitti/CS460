#!/bin/bash

# C source files
SOURCE_FILES=(
    client-step3.complete-reads.c
)

# Output executable name
OUTPUT_NAME="client-step3-complete-reads"

# Compile using GCC
if gcc -Wall "${SOURCE_FILES[@]}" -o "$OUTPUT_NAME" -pthread; then
    echo "Successful compile - output file named '$OUTPUT_NAME'".
else
    echo "Compilation failed".
fi