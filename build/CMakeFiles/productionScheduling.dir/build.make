# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/125/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/125/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/extraDrive/Dev/productionScheduling

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/extraDrive/Dev/productionScheduling/build

# Include any dependencies generated for this target.
include CMakeFiles/productionScheduling.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/productionScheduling.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/productionScheduling.dir/flags.make

CMakeFiles/productionScheduling.dir/main.cpp.o: CMakeFiles/productionScheduling.dir/flags.make
CMakeFiles/productionScheduling.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/extraDrive/Dev/productionScheduling/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/productionScheduling.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/productionScheduling.dir/main.cpp.o -c /mnt/extraDrive/Dev/productionScheduling/main.cpp

CMakeFiles/productionScheduling.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/productionScheduling.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/extraDrive/Dev/productionScheduling/main.cpp > CMakeFiles/productionScheduling.dir/main.cpp.i

CMakeFiles/productionScheduling.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/productionScheduling.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/extraDrive/Dev/productionScheduling/main.cpp -o CMakeFiles/productionScheduling.dir/main.cpp.s

# Object files for target productionScheduling
productionScheduling_OBJECTS = \
"CMakeFiles/productionScheduling.dir/main.cpp.o"

# External object files for target productionScheduling
productionScheduling_EXTERNAL_OBJECTS =

productionScheduling: CMakeFiles/productionScheduling.dir/main.cpp.o
productionScheduling: CMakeFiles/productionScheduling.dir/build.make
productionScheduling: CMakeFiles/productionScheduling.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/extraDrive/Dev/productionScheduling/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable productionScheduling"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/productionScheduling.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/productionScheduling.dir/build: productionScheduling

.PHONY : CMakeFiles/productionScheduling.dir/build

CMakeFiles/productionScheduling.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/productionScheduling.dir/cmake_clean.cmake
.PHONY : CMakeFiles/productionScheduling.dir/clean

CMakeFiles/productionScheduling.dir/depend:
	cd /mnt/extraDrive/Dev/productionScheduling/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/extraDrive/Dev/productionScheduling /mnt/extraDrive/Dev/productionScheduling /mnt/extraDrive/Dev/productionScheduling/build /mnt/extraDrive/Dev/productionScheduling/build /mnt/extraDrive/Dev/productionScheduling/build/CMakeFiles/productionScheduling.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/productionScheduling.dir/depend

