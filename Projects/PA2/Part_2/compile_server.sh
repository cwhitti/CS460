#!/bin/bash

# C source files
SOURCE_FILES=(
    server.c
)

# Output executable name
OUTPUT_NAME="run_server"

# Compile using GCC
gcc -Wall "${SOURCE_FILES[@]}" -o "$OUTPUT_NAME"
