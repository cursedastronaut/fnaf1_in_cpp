#!/bin/bash

# Create the .objects/ directory if it doesn't already exist
mkdir -p .objects

# Function to replicate folder structure
replicate_structure() {
    local source_dir="$1"
    local target_dir=".objects/$source_dir"

    # Find all directories in the source directory and replicate them in the target directory
    find "$source_dir" -type d | while read -r dir; do
        mkdir -p "$target_dir/${dir#$source_dir/}"
    done
}

# Replicate the folder structure of include/ and src/ into .objects/
replicate_structure "include"
replicate_structure "src"

# Run make with any arguments passed to the script
make "$@"
