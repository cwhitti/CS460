#!/bin/bash

# C source files
SOURCE_FILES=(
    client.c
)

# Output executable name
OUTPUT_NAME="run_client"

# Compile using GCC
gcc -Wall "${SOURCE_FILES[@]}" -o "$OUTPUT_NAME"
