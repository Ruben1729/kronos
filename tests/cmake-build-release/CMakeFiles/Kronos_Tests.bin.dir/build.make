# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ruben\OneDrive\Desktop\space\kronos\tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ruben\OneDrive\Desktop\space\kronos\tests\cmake-build-release

# Utility rule file for Kronos_Tests.bin.

# Include any custom commands dependencies for this target.
include CMakeFiles/Kronos_Tests.bin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Kronos_Tests.bin.dir/progress.make

CMakeFiles/Kronos_Tests.bin: Kronos_Tests.elf
	C:\msys64\mingw64\bin\arm-none-eabi-objcopy.exe -O binary ./Kronos_Tests.elf ./Kronos_Tests.bin

Kronos_Tests.bin: CMakeFiles/Kronos_Tests.bin
Kronos_Tests.bin: CMakeFiles/Kronos_Tests.bin.dir/build.make
.PHONY : Kronos_Tests.bin

# Rule to build all files generated by this target.
CMakeFiles/Kronos_Tests.bin.dir/build: Kronos_Tests.bin
.PHONY : CMakeFiles/Kronos_Tests.bin.dir/build

CMakeFiles/Kronos_Tests.bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Kronos_Tests.bin.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Kronos_Tests.bin.dir/clean

CMakeFiles/Kronos_Tests.bin.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ruben\OneDrive\Desktop\space\kronos\tests C:\Users\Ruben\OneDrive\Desktop\space\kronos\tests C:\Users\Ruben\OneDrive\Desktop\space\kronos\tests\cmake-build-release C:\Users\Ruben\OneDrive\Desktop\space\kronos\tests\cmake-build-release C:\Users\Ruben\OneDrive\Desktop\space\kronos\tests\cmake-build-release\CMakeFiles\Kronos_Tests.bin.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Kronos_Tests.bin.dir/depend
