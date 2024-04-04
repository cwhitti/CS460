#!/bin/bash

# C source files
SOURCE_FILES=(
    server-step1.byte-order.c
)

# Output executable name
OUTPUT_NAME="server-step1-byte-order"

# Compile using GCC
if gcc -Wall "${SOURCE_FILES[@]}" -o "$OUTPUT_NAME" -pthread; then
    echo "Successful compile - output file named '$OUTPUT_NAME'".
else
    echo "Compilation failed".
fi