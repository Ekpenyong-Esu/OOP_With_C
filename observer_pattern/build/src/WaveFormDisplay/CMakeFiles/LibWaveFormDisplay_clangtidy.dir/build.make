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
CMAKE_SOURCE_DIR = /home/mahonri/Desktop/OOP_With_C/observer_pattern

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mahonri/Desktop/OOP_With_C/observer_pattern/build

# Utility rule file for LibWaveFormDisplay_clangtidy.

# Include any custom commands dependencies for this target.
include src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/compiler_depend.make

# Include the progress variables for this target.
include src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/progress.make

src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy:
	cd /home/mahonri/Desktop/OOP_With_C/observer_pattern/src/WaveFormDisplay && /usr/bin/python3.10 /home/mahonri/Desktop/OOP_With_C/observer_pattern/tools/run-clang-tidy.py /home/mahonri/Desktop/OOP_With_C/observer_pattern/src/WaveFormDisplay/WaveformDisplay.c /home/mahonri/Desktop/OOP_With_C/observer_pattern/src/WaveFormDisplay/WaveformDisplay.h -config-file=/home/mahonri/Desktop/OOP_With_C/observer_pattern/.clang-tidy -extra-arg-before=-std=99 -header-filter="(src|app)/*.(h|hpp)" -p=/home/mahonri/Desktop/OOP_With_C/observer_pattern/build

LibWaveFormDisplay_clangtidy: src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy
LibWaveFormDisplay_clangtidy: src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/build.make
.PHONY : LibWaveFormDisplay_clangtidy

# Rule to build all files generated by this target.
src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/build: LibWaveFormDisplay_clangtidy
.PHONY : src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/build

src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/clean:
	cd /home/mahonri/Desktop/OOP_With_C/observer_pattern/build/src/WaveFormDisplay && $(CMAKE_COMMAND) -P CMakeFiles/LibWaveFormDisplay_clangtidy.dir/cmake_clean.cmake
.PHONY : src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/clean

src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/depend:
	cd /home/mahonri/Desktop/OOP_With_C/observer_pattern/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mahonri/Desktop/OOP_With_C/observer_pattern /home/mahonri/Desktop/OOP_With_C/observer_pattern/src/WaveFormDisplay /home/mahonri/Desktop/OOP_With_C/observer_pattern/build /home/mahonri/Desktop/OOP_With_C/observer_pattern/build/src/WaveFormDisplay /home/mahonri/Desktop/OOP_With_C/observer_pattern/build/src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/WaveFormDisplay/CMakeFiles/LibWaveFormDisplay_clangtidy.dir/depend

