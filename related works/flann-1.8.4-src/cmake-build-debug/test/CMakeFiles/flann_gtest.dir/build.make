# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\flann-1.8.4-src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\flann-1.8.4-src\cmake-build-debug"

# Utility rule file for flann_gtest.

# Include the progress variables for this target.
include test/CMakeFiles/flann_gtest.dir/progress.make

flann_gtest: test/CMakeFiles/flann_gtest.dir/build.make

.PHONY : flann_gtest

# Rule to build all files generated by this target.
test/CMakeFiles/flann_gtest.dir/build: flann_gtest

.PHONY : test/CMakeFiles/flann_gtest.dir/build

test/CMakeFiles/flann_gtest.dir/clean:
	cd /d C:\Users\markz\Desktop\KNN-GR~1\KNN-GR~1\RELATE~1\FLANN-~1.4-S\CMAKE-~1\test && $(CMAKE_COMMAND) -P CMakeFiles\flann_gtest.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/flann_gtest.dir/clean

test/CMakeFiles/flann_gtest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\flann-1.8.4-src" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\flann-1.8.4-src\test" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\flann-1.8.4-src\cmake-build-debug" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\flann-1.8.4-src\cmake-build-debug\test" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\flann-1.8.4-src\cmake-build-debug\test\CMakeFiles\flann_gtest.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : test/CMakeFiles/flann_gtest.dir/depend

