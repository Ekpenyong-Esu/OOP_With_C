# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/mahonri/Desktop/OOP_With_C/adapter_pattern

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build

# Include any dependencies generated for this target.
include src/GasMixer/CMakeFiles/LibGasMixer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/GasMixer/CMakeFiles/LibGasMixer.dir/compiler_depend.make

# Include the progress variables for this target.
include src/GasMixer/CMakeFiles/LibGasMixer.dir/progress.make

# Include the compile flags for this target's objects.
include src/GasMixer/CMakeFiles/LibGasMixer.dir/flags.make

src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.o: src/GasMixer/CMakeFiles/LibGasMixer.dir/flags.make
src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.o: ../src/GasMixer/GasMixer.c
src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.o: src/GasMixer/CMakeFiles/LibGasMixer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.o"
	cd /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.o -MF CMakeFiles/LibGasMixer.dir/GasMixer.c.o.d -o CMakeFiles/LibGasMixer.dir/GasMixer.c.o -c /home/mahonri/Desktop/OOP_With_C/adapter_pattern/src/GasMixer/GasMixer.c

src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibGasMixer.dir/GasMixer.c.i"
	cd /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mahonri/Desktop/OOP_With_C/adapter_pattern/src/GasMixer/GasMixer.c > CMakeFiles/LibGasMixer.dir/GasMixer.c.i

src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibGasMixer.dir/GasMixer.c.s"
	cd /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mahonri/Desktop/OOP_With_C/adapter_pattern/src/GasMixer/GasMixer.c -o CMakeFiles/LibGasMixer.dir/GasMixer.c.s

# Object files for target LibGasMixer
LibGasMixer_OBJECTS = \
"CMakeFiles/LibGasMixer.dir/GasMixer.c.o"

# External object files for target LibGasMixer
LibGasMixer_EXTERNAL_OBJECTS =

src/GasMixer/libLibGasMixer.a: src/GasMixer/CMakeFiles/LibGasMixer.dir/GasMixer.c.o
src/GasMixer/libLibGasMixer.a: src/GasMixer/CMakeFiles/LibGasMixer.dir/build.make
src/GasMixer/libLibGasMixer.a: src/GasMixer/CMakeFiles/LibGasMixer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libLibGasMixer.a"
	cd /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer && $(CMAKE_COMMAND) -P CMakeFiles/LibGasMixer.dir/cmake_clean_target.cmake
	cd /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LibGasMixer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/GasMixer/CMakeFiles/LibGasMixer.dir/build: src/GasMixer/libLibGasMixer.a
.PHONY : src/GasMixer/CMakeFiles/LibGasMixer.dir/build

src/GasMixer/CMakeFiles/LibGasMixer.dir/clean:
	cd /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer && $(CMAKE_COMMAND) -P CMakeFiles/LibGasMixer.dir/cmake_clean.cmake
.PHONY : src/GasMixer/CMakeFiles/LibGasMixer.dir/clean

src/GasMixer/CMakeFiles/LibGasMixer.dir/depend:
	cd /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mahonri/Desktop/OOP_With_C/adapter_pattern /home/mahonri/Desktop/OOP_With_C/adapter_pattern/src/GasMixer /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer /home/mahonri/Desktop/OOP_With_C/adapter_pattern/build/src/GasMixer/CMakeFiles/LibGasMixer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/GasMixer/CMakeFiles/LibGasMixer.dir/depend

