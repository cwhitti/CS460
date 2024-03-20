#!/bin/bash

# C source files
SOURCE_FILES=(
    server-step1.no-frills.c
)

# Output executable name
OUTPUT_NAME="server-step1-no-frills"

# Compile using GCC
if gcc -Wall "${SOURCE_FILES[@]}" -o "$OUTPUT_NAME"; then
    echo "Successful compile - output file named '$OUTPUT_NAME'".
else
    echo "Compilation failed".
fi