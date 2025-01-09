#!/bin/bash

# Prompt user to select installation option
echo "Please select an installation option:"
echo "1. Install libsgl"
echo "2. Create a new project with libsgl"
read -r option

case $option in
  1)
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
    ;;

  2)
    # Prompt user to enter project directory and name
    echo "Please enter the project directory:"
    read -r project_dir

    echo "Please enter the project name:"
    read -r project_name

    echo "Done."
    ;;

  *)
    echo "Invalid option. Exiting."
    exit 1
    ;;
esac
