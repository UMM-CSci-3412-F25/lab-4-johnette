#!/bin/bash
set -euo pipefail

# Check if exactly one argument was provided
if [ "$#" -ne 1 ]; then
    echo "Error: Missing required argument."
    echo "Usage: $0 <path>"
    echo "       where <path> is the file or root of the tree you want to summarize."
    exit 1
fi

START_PATH="$1"

# Check if the path exists
if [ ! -e "$START_PATH" ]; then
    echo "Error: '$START_PATH' does not exist."
    exit 2
fi

# Check if the path is readable
if [ ! -r "$START_PATH" ]; then
    echo "Error: '$START_PATH' is not readable. Check permissions."
    exit 3
fi

# Check if the path is a file or directory
if [ ! -d "$START_PATH" ] && [ ! -f "$START_PATH" ]; then
    echo "Error: '$START_PATH' is neither a file nor a directory."
    exit 4
fi

# Count directories (excluding the root itself)
NUM_DIRS=$(find "$START_PATH" -type d | wc -l)

# Count regular files
NUM_REGULAR=$(find "$START_PATH" -type f | wc -l)

# Optional: Count symbolic links
NUM_SYMLINKS=$(find "$START_PATH" -type l | wc -l)

# Print summary
echo "Processed all the files from $START_PATH."
echo "There were $NUM_DIRS directories."
echo "There were $NUM_REGULAR regular files."
# echo "There were $NUM_SYMLINKS symbolic links."

# Handle empty results
if [ "$NUM_DIRS" -eq 0 ] && [ "$NUM_REGULAR" -eq 0 ]; then
    echo "Note: No directories or regular files found under \"$START_PATH\"."
fi
exit 0