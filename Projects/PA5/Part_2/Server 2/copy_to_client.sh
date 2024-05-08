#!/bin/bash

srcDir="./src/"
destDir="../Client/src/"

filesToCopy=(message.c message.h chat_node.c chat_node.h)

for file in "${filesToCopy[@]}"; do
    cp $srcDir$file $destDir$file
done