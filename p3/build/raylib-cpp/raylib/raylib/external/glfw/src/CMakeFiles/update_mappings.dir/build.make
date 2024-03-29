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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/daniela_castorena/Desktop/MiniProjects/p3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daniela_castorena/Desktop/MiniProjects/p3/build

# Utility rule file for update_mappings.

# Include any custom commands dependencies for this target.
include raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/compiler_depend.make

# Include the progress variables for this target.
include raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/progress.make

raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/daniela_castorena/Desktop/MiniProjects/p3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Updating gamepad mappings from upstream repository"
	cd /Users/daniela_castorena/Desktop/MiniProjects/p3/raylib-cpp/raylib/src/external/glfw/src && /opt/homebrew/Cellar/cmake/3.28.2/bin/cmake -P /Users/daniela_castorena/Desktop/MiniProjects/p3/raylib-cpp/raylib/src/external/glfw/CMake/GenerateMappings.cmake mappings.h.in mappings.h

update_mappings: raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings
update_mappings: raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build.make
.PHONY : update_mappings

# Rule to build all files generated by this target.
raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build: update_mappings
.PHONY : raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build

raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/clean:
	cd /Users/daniela_castorena/Desktop/MiniProjects/p3/build/raylib-cpp/raylib/raylib/external/glfw/src && $(CMAKE_COMMAND) -P CMakeFiles/update_mappings.dir/cmake_clean.cmake
.PHONY : raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/clean

raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/depend:
	cd /Users/daniela_castorena/Desktop/MiniProjects/p3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daniela_castorena/Desktop/MiniProjects/p3 /Users/daniela_castorena/Desktop/MiniProjects/p3/raylib-cpp/raylib/src/external/glfw/src /Users/daniela_castorena/Desktop/MiniProjects/p3/build /Users/daniela_castorena/Desktop/MiniProjects/p3/build/raylib-cpp/raylib/raylib/external/glfw/src /Users/daniela_castorena/Desktop/MiniProjects/p3/build/raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : raylib-cpp/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/depend

