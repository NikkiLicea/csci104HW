# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /work/hw-nlicea/hw2/hw2_tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/hw-nlicea/hw2/hw2_tests

# Utility rule file for debug-Cmdhandlers.OrHandler.

# Include the progress variables for this target.
include cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/progress.make

cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/hw-nlicea/hw2/hw2_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging Cmdhandlers.OrHandler with GDB..."
	cd /work/hw-nlicea/hw2 && gdb --args /work/hw-nlicea/hw2/hw2_tests/cmdhandler_tests/cmdhandler_tests --gtest_filter=Cmdhandlers.OrHandler

debug-Cmdhandlers.OrHandler: cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler
debug-Cmdhandlers.OrHandler: cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/build.make

.PHONY : debug-Cmdhandlers.OrHandler

# Rule to build all files generated by this target.
cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/build: debug-Cmdhandlers.OrHandler

.PHONY : cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/build

cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/clean:
	cd /work/hw-nlicea/hw2/hw2_tests/cmdhandler_tests && $(CMAKE_COMMAND) -P CMakeFiles/debug-Cmdhandlers.OrHandler.dir/cmake_clean.cmake
.PHONY : cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/clean

cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/depend:
	cd /work/hw-nlicea/hw2/hw2_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/hw-nlicea/hw2/hw2_tests /work/hw-nlicea/hw2/hw2_tests/cmdhandler_tests /work/hw-nlicea/hw2/hw2_tests /work/hw-nlicea/hw2/hw2_tests/cmdhandler_tests /work/hw-nlicea/hw2/hw2_tests/cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cmdhandler_tests/CMakeFiles/debug-Cmdhandlers.OrHandler.dir/depend

