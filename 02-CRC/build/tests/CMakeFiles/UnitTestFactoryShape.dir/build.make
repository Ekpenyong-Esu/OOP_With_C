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
include tests/CMakeFiles/UnitTestFactoryShape.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/UnitTestFactoryShape.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/UnitTestFactoryShape.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/UnitTestFactoryShape.dir/flags.make

tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o: tests/CMakeFiles/UnitTestFactoryShape.dir/flags.make
tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o: ../tests/test_factory_shape.c
tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o: tests/CMakeFiles/UnitTestFactoryShape.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/tests && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o -MF CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o.d -o CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o -c /home/mahonri/Desktop/Factory_Design_Pattern_COOP/tests/test_factory_shape.c

tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.i"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/tests && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mahonri/Desktop/Factory_Design_Pattern_COOP/tests/test_factory_shape.c > CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.i

tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.s"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/tests && /usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mahonri/Desktop/Factory_Design_Pattern_COOP/tests/test_factory_shape.c -o CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.s

# Object files for target UnitTestFactoryShape
UnitTestFactoryShape_OBJECTS = \
"CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o"

# External object files for target UnitTestFactoryShape
UnitTestFactoryShape_EXTERNAL_OBJECTS =

tests/UnitTestFactoryShape: tests/CMakeFiles/UnitTestFactoryShape.dir/test_factory_shape.c.o
tests/UnitTestFactoryShape: tests/CMakeFiles/UnitTestFactoryShape.dir/build.make
tests/UnitTestFactoryShape: src/shape_factory/libLibShapeFactory.a
tests/UnitTestFactoryShape: _deps/unity-build/libunity.a
tests/UnitTestFactoryShape: src/circle/libLibCircle.a
tests/UnitTestFactoryShape: src/rectangle/libLibRectangle.a
tests/UnitTestFactoryShape: src/triangle/libLibTriangle.a
tests/UnitTestFactoryShape: src/shape/libLibShape.a
tests/UnitTestFactoryShape: tests/CMakeFiles/UnitTestFactoryShape.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable UnitTestFactoryShape"
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UnitTestFactoryShape.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/UnitTestFactoryShape.dir/build: tests/UnitTestFactoryShape
.PHONY : tests/CMakeFiles/UnitTestFactoryShape.dir/build

tests/CMakeFiles/UnitTestFactoryShape.dir/clean:
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/UnitTestFactoryShape.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/UnitTestFactoryShape.dir/clean

tests/CMakeFiles/UnitTestFactoryShape.dir/depend:
	cd /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mahonri/Desktop/Factory_Design_Pattern_COOP /home/mahonri/Desktop/Factory_Design_Pattern_COOP/tests /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/tests /home/mahonri/Desktop/Factory_Design_Pattern_COOP/build/tests/CMakeFiles/UnitTestFactoryShape.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/UnitTestFactoryShape.dir/depend
