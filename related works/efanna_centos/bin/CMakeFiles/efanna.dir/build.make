# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake3

# The command to remove a file.
RM = /usr/bin/cmake3 -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/LengYue/Repository/KNN-Graph/related works/efanna"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/LengYue/Repository/KNN-Graph/related works/efanna/bin"

# Include any dependencies generated for this target.
include CMakeFiles/efanna.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/efanna.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/efanna.dir/flags.make

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o: CMakeFiles/efanna.dir/flags.make
CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o: ../samples/efanna_index_buildall.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/LengYue/Repository/KNN-Graph/related works/efanna/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o -c "/home/LengYue/Repository/KNN-Graph/related works/efanna/samples/efanna_index_buildall.cc"

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/LengYue/Repository/KNN-Graph/related works/efanna/samples/efanna_index_buildall.cc" > CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.i

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/LengYue/Repository/KNN-Graph/related works/efanna/samples/efanna_index_buildall.cc" -o CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.s

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.requires:

.PHONY : CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.requires

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.provides: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.requires
	$(MAKE) -f CMakeFiles/efanna.dir/build.make CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.provides.build
.PHONY : CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.provides

CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.provides.build: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o


# Object files for target efanna
efanna_OBJECTS = \
"CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o"

# External object files for target efanna
efanna_EXTERNAL_OBJECTS =

efanna: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o
efanna: CMakeFiles/efanna.dir/build.make
efanna: CMakeFiles/efanna.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/LengYue/Repository/KNN-Graph/related works/efanna/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable efanna"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/efanna.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/efanna.dir/build: efanna

.PHONY : CMakeFiles/efanna.dir/build

CMakeFiles/efanna.dir/requires: CMakeFiles/efanna.dir/samples/efanna_index_buildall.cc.o.requires

.PHONY : CMakeFiles/efanna.dir/requires

CMakeFiles/efanna.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/efanna.dir/cmake_clean.cmake
.PHONY : CMakeFiles/efanna.dir/clean

CMakeFiles/efanna.dir/depend:
	cd "/home/LengYue/Repository/KNN-Graph/related works/efanna/bin" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/LengYue/Repository/KNN-Graph/related works/efanna" "/home/LengYue/Repository/KNN-Graph/related works/efanna" "/home/LengYue/Repository/KNN-Graph/related works/efanna/bin" "/home/LengYue/Repository/KNN-Graph/related works/efanna/bin" "/home/LengYue/Repository/KNN-Graph/related works/efanna/bin/CMakeFiles/efanna.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/efanna.dir/depend

