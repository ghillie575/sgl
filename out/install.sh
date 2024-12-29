#!/bin/bash

# Prompt user to enter install directory
echo "Please enter the install directory:"
read -r install_dir

# Check if directory exists, if not create it
if [ ! -d "$install_dir" ]; then
  mkdir -pv "$install_dir" || { echo "Failed to create directory: $install_dir"; exit 1; }
  echo "Directory created: $install_dir"
else
  echo "Directory already exists: $install_dir, skipping"
fi

# Change into the install directory
cd "$install_dir" || { echo "Failed to change directory to: $install_dir"; exit 1; }

# Install program (replace with actual installation command)
echo "Installing program..."

# Create lib and include directories
mkdir -pv "$install_dir/lib" || { echo "Failed to create lib directory"; exit 1; }
mkdir -pv "$install_dir/include" || { echo "Failed to create include directory"; exit 1; }

# Copy files with error handling
cp -fv ./libsgl.so "$install_dir/lib" || { echo "Failed to copy libsgl.so"; exit 1; }
echo "libsgl.so copied to $install_dir/lib"

cp -rfv ./include "$install_dir/include" || { echo "Failed to copy include directory"; exit 1; }
echo "Include directory copied to $install_dir/include"

echo "Installation completed successfully."