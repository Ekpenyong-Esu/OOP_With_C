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
CMAKE_SOURCE_DIR = /home/mahonri/Desktop/Factory_Design_Pattern_COOP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build

# Include any dependencies generated for this target.
include src/triangle/CMakeFiles/LibTriangle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/triangle/CMakeFiles/LibTriangle.dir/compiler_depend.make

# Include the progress variables for this target.
include src/triangle/CMakeFiles/LibTriangle.dir/progress.make

# Include the compile flags for this target's objects.
include src/triangle/CMakeFiles/LibTriangle.dir/flags.make

src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.o: src/triangle/CMakeFiles/LibTriangle.dir/flags.make
src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.o: ../src/triangle/triangle.c
src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.o: src/triangle/CMakeFiles/LibTriangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.o"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.o -MF CMakeFiles/LibTriangle.dir/triangle.c.o.d -o CMakeFiles/LibTriangle.dir/triangle.c.o -c /home/mahonri/Desktop/Factory_Design_Pattern_COOP/src/triangle/triangle.c

src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibTriangle.dir/triangle.c.i"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mahonri/Desktop/Factory_Design_Pattern_COOP/src/triangle/triangle.c > CMakeFiles/LibTriangle.dir/triangle.c.i

src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibTriangle.dir/triangle.c.s"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mahonri/Desktop/Factory_Design_Pattern_COOP/src/triangle/triangle.c -o CMakeFiles/LibTriangle.dir/triangle.c.s

# Object files for target LibTriangle
LibTriangle_OBJECTS = \
"CMakeFiles/LibTriangle.dir/triangle.c.o"

# External object files for target LibTriangle
LibTriangle_EXTERNAL_OBJECTS =

src/triangle/libLibTriangle.a: src/triangle/CMakeFiles/LibTriangle.dir/triangle.c.o
src/triangle/libLibTriangle.a: src/triangle/CMakeFiles/LibTriangle.dir/build.make
src/triangle/libLibTriangle.a: src/triangle/CMakeFiles/LibTriangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libLibTriangle.a"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle && $(CMAKE_COMMAND) -P CMakeFiles/LibTriangle.dir/cmake_clean_target.cmake
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LibTriangle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/triangle/CMakeFiles/LibTriangle.dir/build: src/triangle/libLibTriangle.a
.PHONY : src/triangle/CMakeFiles/LibTriangle.dir/build

src/triangle/CMakeFiles/LibTriangle.dir/clean:
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle && $(CMAKE_COMMAND) -P CMakeFiles/LibTriangle.dir/cmake_clean.cmake
.PHONY : src/triangle/CMakeFiles/LibTriangle.dir/clean

src/triangle/CMakeFiles/LibTriangle.dir/depend:
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mahonri/Desktop/Factory_Design_Pattern_COOP /home/mahonri/Desktop/Factory_Design_Pattern_COOP/src/triangle /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/src/triangle/CMakeFiles/LibTriangle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/triangle/CMakeFiles/LibTriangle.dir/depend
