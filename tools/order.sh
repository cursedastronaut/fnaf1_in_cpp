#!/bin/bash

# Set paths for unordered and ordered folders
unordered_folder="unordered"     # Path to the original unordered folder with files named 0.png to 605.png
ordered_folder="ordered"         # Path to the ordered folder with files organized in subfolders

# Output script file
output_script="move_files.sh"

# Start writing the generated script
echo "#!/bin/bash" > "$output_script"
echo "" >> "$output_script"

# Loop through each .png file in the ordered folder
find "$ordered_folder" -type f -name "*.png" | while read -r ordered_file_path; do
    # Get the base filename (e.g., "0.png", "1.png", etc.)
    filename=$(basename "$ordered_file_path")
    
    # Determine the relative directory structure within the ordered folder
    relative_dir=$(dirname "${ordered_file_path#$ordered_folder/}")
    
    # Add commands to create the directory and move the file in the output script
    echo "mkdir -p \"$unordered_folder/$relative_dir\"" >> "$output_script"
    echo "mv \"$unordered_folder/$filename\" \"$unordered_folder/$relative_dir/\"" >> "$output_script"
done

# Make the generated script executable
chmod +x "$output_script"

echo "Script $output_script has been generated. Run it to organize files."
