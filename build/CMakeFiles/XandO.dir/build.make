# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/mikhail/Files/Projects/xAndo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/mikhail/Files/Projects/xAndo/build

# Include any dependencies generated for this target.
include CMakeFiles/XandO.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/XandO.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/XandO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XandO.dir/flags.make

CMakeFiles/XandO.dir/main.cpp.o: CMakeFiles/XandO.dir/flags.make
CMakeFiles/XandO.dir/main.cpp.o: /media/mikhail/Files/Projects/xAndo/main.cpp
CMakeFiles/XandO.dir/main.cpp.o: CMakeFiles/XandO.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/mikhail/Files/Projects/xAndo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/XandO.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XandO.dir/main.cpp.o -MF CMakeFiles/XandO.dir/main.cpp.o.d -o CMakeFiles/XandO.dir/main.cpp.o -c /media/mikhail/Files/Projects/xAndo/main.cpp

CMakeFiles/XandO.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/XandO.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/mikhail/Files/Projects/xAndo/main.cpp > CMakeFiles/XandO.dir/main.cpp.i

CMakeFiles/XandO.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/XandO.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/mikhail/Files/Projects/xAndo/main.cpp -o CMakeFiles/XandO.dir/main.cpp.s

CMakeFiles/XandO.dir/src/shader.cpp.o: CMakeFiles/XandO.dir/flags.make
CMakeFiles/XandO.dir/src/shader.cpp.o: /media/mikhail/Files/Projects/xAndo/src/shader.cpp
CMakeFiles/XandO.dir/src/shader.cpp.o: CMakeFiles/XandO.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/mikhail/Files/Projects/xAndo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/XandO.dir/src/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XandO.dir/src/shader.cpp.o -MF CMakeFiles/XandO.dir/src/shader.cpp.o.d -o CMakeFiles/XandO.dir/src/shader.cpp.o -c /media/mikhail/Files/Projects/xAndo/src/shader.cpp

CMakeFiles/XandO.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/XandO.dir/src/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/mikhail/Files/Projects/xAndo/src/shader.cpp > CMakeFiles/XandO.dir/src/shader.cpp.i

CMakeFiles/XandO.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/XandO.dir/src/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/mikhail/Files/Projects/xAndo/src/shader.cpp -o CMakeFiles/XandO.dir/src/shader.cpp.s

CMakeFiles/XandO.dir/src/glad.c.o: CMakeFiles/XandO.dir/flags.make
CMakeFiles/XandO.dir/src/glad.c.o: /media/mikhail/Files/Projects/xAndo/src/glad.c
CMakeFiles/XandO.dir/src/glad.c.o: CMakeFiles/XandO.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/mikhail/Files/Projects/xAndo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/XandO.dir/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XandO.dir/src/glad.c.o -MF CMakeFiles/XandO.dir/src/glad.c.o.d -o CMakeFiles/XandO.dir/src/glad.c.o -c /media/mikhail/Files/Projects/xAndo/src/glad.c

CMakeFiles/XandO.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/XandO.dir/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/mikhail/Files/Projects/xAndo/src/glad.c > CMakeFiles/XandO.dir/src/glad.c.i

CMakeFiles/XandO.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/XandO.dir/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/mikhail/Files/Projects/xAndo/src/glad.c -o CMakeFiles/XandO.dir/src/glad.c.s

CMakeFiles/XandO.dir/src/window.cpp.o: CMakeFiles/XandO.dir/flags.make
CMakeFiles/XandO.dir/src/window.cpp.o: /media/mikhail/Files/Projects/xAndo/src/window.cpp
CMakeFiles/XandO.dir/src/window.cpp.o: CMakeFiles/XandO.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/mikhail/Files/Projects/xAndo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/XandO.dir/src/window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XandO.dir/src/window.cpp.o -MF CMakeFiles/XandO.dir/src/window.cpp.o.d -o CMakeFiles/XandO.dir/src/window.cpp.o -c /media/mikhail/Files/Projects/xAndo/src/window.cpp

CMakeFiles/XandO.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/XandO.dir/src/window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/mikhail/Files/Projects/xAndo/src/window.cpp > CMakeFiles/XandO.dir/src/window.cpp.i

CMakeFiles/XandO.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/XandO.dir/src/window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/mikhail/Files/Projects/xAndo/src/window.cpp -o CMakeFiles/XandO.dir/src/window.cpp.s

CMakeFiles/XandO.dir/src/object.cpp.o: CMakeFiles/XandO.dir/flags.make
CMakeFiles/XandO.dir/src/object.cpp.o: /media/mikhail/Files/Projects/xAndo/src/object.cpp
CMakeFiles/XandO.dir/src/object.cpp.o: CMakeFiles/XandO.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/mikhail/Files/Projects/xAndo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/XandO.dir/src/object.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XandO.dir/src/object.cpp.o -MF CMakeFiles/XandO.dir/src/object.cpp.o.d -o CMakeFiles/XandO.dir/src/object.cpp.o -c /media/mikhail/Files/Projects/xAndo/src/object.cpp

CMakeFiles/XandO.dir/src/object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/XandO.dir/src/object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/mikhail/Files/Projects/xAndo/src/object.cpp > CMakeFiles/XandO.dir/src/object.cpp.i

CMakeFiles/XandO.dir/src/object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/XandO.dir/src/object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/mikhail/Files/Projects/xAndo/src/object.cpp -o CMakeFiles/XandO.dir/src/object.cpp.s

# Object files for target XandO
XandO_OBJECTS = \
"CMakeFiles/XandO.dir/main.cpp.o" \
"CMakeFiles/XandO.dir/src/shader.cpp.o" \
"CMakeFiles/XandO.dir/src/glad.c.o" \
"CMakeFiles/XandO.dir/src/window.cpp.o" \
"CMakeFiles/XandO.dir/src/object.cpp.o"

# External object files for target XandO
XandO_EXTERNAL_OBJECTS =

XandO: CMakeFiles/XandO.dir/main.cpp.o
XandO: CMakeFiles/XandO.dir/src/shader.cpp.o
XandO: CMakeFiles/XandO.dir/src/glad.c.o
XandO: CMakeFiles/XandO.dir/src/window.cpp.o
XandO: CMakeFiles/XandO.dir/src/object.cpp.o
XandO: CMakeFiles/XandO.dir/build.make
XandO: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
XandO: /usr/lib/x86_64-linux-gnu/libGL.so
XandO: CMakeFiles/XandO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/media/mikhail/Files/Projects/xAndo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable XandO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XandO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XandO.dir/build: XandO
.PHONY : CMakeFiles/XandO.dir/build

CMakeFiles/XandO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XandO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XandO.dir/clean

CMakeFiles/XandO.dir/depend:
	cd /media/mikhail/Files/Projects/xAndo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/mikhail/Files/Projects/xAndo /media/mikhail/Files/Projects/xAndo /media/mikhail/Files/Projects/xAndo/build /media/mikhail/Files/Projects/xAndo/build /media/mikhail/Files/Projects/xAndo/build/CMakeFiles/XandO.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/XandO.dir/depend

