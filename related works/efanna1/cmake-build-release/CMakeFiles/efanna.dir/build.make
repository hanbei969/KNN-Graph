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
CMAKE_SOURCE_DIR = "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\cmake-build-release"

# Include any dependencies generated for this target.
include CMakeFiles/efanna.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/efanna.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/efanna.dir/flags.make

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj: CMakeFiles/efanna.dir/flags.make
CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj: CMakeFiles/efanna.dir/includes_CXX.rsp
CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj: ../samples/efanna_index_buildall.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\efanna.dir\samples\efanna_index_buildall.cc.obj -c "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\samples\efanna_index_buildall.cc"

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\samples\efanna_index_buildall.cc" > CMakeFiles\efanna.dir\samples\efanna_index_buildall.cc.i

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\samples\efanna_index_buildall.cc" -o CMakeFiles\efanna.dir\samples\efanna_index_buildall.cc.s

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.requires:

.PHONY : CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.requires

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.provides: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.requires
	$(MAKE) -f CMakeFiles\efanna.dir\build.make CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.provides.build
.PHONY : CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.provides

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.provides.build: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj


# Object files for target efanna
efanna_OBJECTS = \
"CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj"

# External object files for target efanna
efanna_EXTERNAL_OBJECTS =

efanna.exe: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj
efanna.exe: CMakeFiles/efanna.dir/build.make
efanna.exe: CMakeFiles/efanna.dir/linklibs.rsp
efanna.exe: CMakeFiles/efanna.dir/objects1.rsp
efanna.exe: CMakeFiles/efanna.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable efanna.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\efanna.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/efanna.dir/build: efanna.exe

.PHONY : CMakeFiles/efanna.dir/build

CMakeFiles/efanna.dir/requires: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.obj.requires

.PHONY : CMakeFiles/efanna.dir/requires

CMakeFiles/efanna.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\efanna.dir\cmake_clean.cmake
.PHONY : CMakeFiles/efanna.dir/clean

CMakeFiles/efanna.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\cmake-build-release" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\cmake-build-release" "C:\Users\markz\Desktop\KNN-Graph\KNN-Graph\related works\efanna\cmake-build-release\CMakeFiles\efanna.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/efanna.dir/depend
