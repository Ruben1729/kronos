# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Applications\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Applications\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles\Kronos_lib.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Kronos_lib.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Kronos_lib.dir\flags.make

CMakeFiles\Kronos_lib.dir\src\main.obj: CMakeFiles\Kronos_lib.dir\flags.make
CMakeFiles\Kronos_lib.dir\src\main.obj: ..\src\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Kronos_lib.dir/src/main.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Kronos_lib.dir\src\main.obj /FdCMakeFiles\Kronos_lib.dir\Kronos_lib.pdb /FS -c C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\src\main.cpp
<<

CMakeFiles\Kronos_lib.dir\src\main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kronos_lib.dir/src/main.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe > CMakeFiles\Kronos_lib.dir\src\main.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\src\main.cpp
<<

CMakeFiles\Kronos_lib.dir\src\main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kronos_lib.dir/src/main.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Kronos_lib.dir\src\main.s /c C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\src\main.cpp
<<

# Object files for target Kronos_lib
Kronos_lib_OBJECTS = \
"CMakeFiles\Kronos_lib.dir\src\main.obj"

# External object files for target Kronos_lib
Kronos_lib_EXTERNAL_OBJECTS =

Kronos_lib.lib: CMakeFiles\Kronos_lib.dir\src\main.obj
Kronos_lib.lib: CMakeFiles\Kronos_lib.dir\build.make
Kronos_lib.lib: CMakeFiles\Kronos_lib.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library Kronos_lib.lib"
	$(CMAKE_COMMAND) -P CMakeFiles\Kronos_lib.dir\cmake_clean_target.cmake
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\link.exe /lib /nologo /machine:x64 /out:Kronos_lib.lib @CMakeFiles\Kronos_lib.dir\objects1.rsp 

# Rule to build all files generated by this target.
CMakeFiles\Kronos_lib.dir\build: Kronos_lib.lib

.PHONY : CMakeFiles\Kronos_lib.dir\build

CMakeFiles\Kronos_lib.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Kronos_lib.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Kronos_lib.dir\clean

CMakeFiles\Kronos_lib.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\cmake-build-release C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\cmake-build-release C:\Users\Ruben\OneDrive\Desktop\space\kronos\Kronos_lib\cmake-build-release\CMakeFiles\Kronos_lib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Kronos_lib.dir\depend

