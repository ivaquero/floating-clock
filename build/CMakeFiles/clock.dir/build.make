# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/integzz/Documents/proj-clock

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/integzz/Documents/proj-clock/build

# Include any dependencies generated for this target.
include CMakeFiles/clock.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/clock.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/clock.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clock.dir/flags.make

CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o: CMakeFiles/clock.dir/flags.make
CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o: clock_autogen/mocs_compilation.cpp
CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o: CMakeFiles/clock.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/integzz/Documents/proj-clock/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o -MF CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o -c /Users/integzz/Documents/proj-clock/build/clock_autogen/mocs_compilation.cpp

CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/integzz/Documents/proj-clock/build/clock_autogen/mocs_compilation.cpp > CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.i

CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/integzz/Documents/proj-clock/build/clock_autogen/mocs_compilation.cpp -o CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.s

CMakeFiles/clock.dir/clock.cpp.o: CMakeFiles/clock.dir/flags.make
CMakeFiles/clock.dir/clock.cpp.o: /Users/integzz/Documents/proj-clock/clock.cpp
CMakeFiles/clock.dir/clock.cpp.o: CMakeFiles/clock.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/integzz/Documents/proj-clock/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/clock.dir/clock.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/clock.dir/clock.cpp.o -MF CMakeFiles/clock.dir/clock.cpp.o.d -o CMakeFiles/clock.dir/clock.cpp.o -c /Users/integzz/Documents/proj-clock/clock.cpp

CMakeFiles/clock.dir/clock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clock.dir/clock.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/integzz/Documents/proj-clock/clock.cpp > CMakeFiles/clock.dir/clock.cpp.i

CMakeFiles/clock.dir/clock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clock.dir/clock.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/integzz/Documents/proj-clock/clock.cpp -o CMakeFiles/clock.dir/clock.cpp.s

CMakeFiles/clock.dir/main.cpp.o: CMakeFiles/clock.dir/flags.make
CMakeFiles/clock.dir/main.cpp.o: /Users/integzz/Documents/proj-clock/main.cpp
CMakeFiles/clock.dir/main.cpp.o: CMakeFiles/clock.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/integzz/Documents/proj-clock/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/clock.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/clock.dir/main.cpp.o -MF CMakeFiles/clock.dir/main.cpp.o.d -o CMakeFiles/clock.dir/main.cpp.o -c /Users/integzz/Documents/proj-clock/main.cpp

CMakeFiles/clock.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/clock.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/integzz/Documents/proj-clock/main.cpp > CMakeFiles/clock.dir/main.cpp.i

CMakeFiles/clock.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/clock.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/integzz/Documents/proj-clock/main.cpp -o CMakeFiles/clock.dir/main.cpp.s

# Object files for target clock
clock_OBJECTS = \
"CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/clock.dir/clock.cpp.o" \
"CMakeFiles/clock.dir/main.cpp.o"

# External object files for target clock
clock_EXTERNAL_OBJECTS =

clock: CMakeFiles/clock.dir/clock_autogen/mocs_compilation.cpp.o
clock: CMakeFiles/clock.dir/clock.cpp.o
clock: CMakeFiles/clock.dir/main.cpp.o
clock: CMakeFiles/clock.dir/build.make
clock: /opt/homebrew/opt/qt@5/lib/QtWidgets.framework/QtWidgets
clock: /opt/homebrew/opt/qt@5/lib/QtGui.framework/QtGui
clock: /opt/homebrew/opt/qt@5/lib/QtCore.framework/QtCore
clock: CMakeFiles/clock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/integzz/Documents/proj-clock/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable clock"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clock.dir/build: clock
.PHONY : CMakeFiles/clock.dir/build

CMakeFiles/clock.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clock.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clock.dir/clean

CMakeFiles/clock.dir/depend:
	cd /Users/integzz/Documents/proj-clock/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/integzz/Documents/proj-clock /Users/integzz/Documents/proj-clock /Users/integzz/Documents/proj-clock/build /Users/integzz/Documents/proj-clock/build /Users/integzz/Documents/proj-clock/build/CMakeFiles/clock.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/clock.dir/depend
