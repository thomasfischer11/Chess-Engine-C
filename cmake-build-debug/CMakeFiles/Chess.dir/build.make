# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /snap/clion/209/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/209/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thomas/CLionProjects/Chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/CLionProjects/Chess/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Chess.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Chess.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Chess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chess.dir/flags.make

CMakeFiles/Chess.dir/main.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/main.cpp.o: ../main.cpp
CMakeFiles/Chess.dir/main.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas/CLionProjects/Chess/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chess.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/main.cpp.o -MF CMakeFiles/Chess.dir/main.cpp.o.d -o CMakeFiles/Chess.dir/main.cpp.o -c /home/thomas/CLionProjects/Chess/main.cpp

CMakeFiles/Chess.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas/CLionProjects/Chess/main.cpp > CMakeFiles/Chess.dir/main.cpp.i

CMakeFiles/Chess.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas/CLionProjects/Chess/main.cpp -o CMakeFiles/Chess.dir/main.cpp.s

CMakeFiles/Chess.dir/Position.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/Position.cpp.o: ../Position.cpp
CMakeFiles/Chess.dir/Position.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas/CLionProjects/Chess/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Chess.dir/Position.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/Position.cpp.o -MF CMakeFiles/Chess.dir/Position.cpp.o.d -o CMakeFiles/Chess.dir/Position.cpp.o -c /home/thomas/CLionProjects/Chess/Position.cpp

CMakeFiles/Chess.dir/Position.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/Position.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas/CLionProjects/Chess/Position.cpp > CMakeFiles/Chess.dir/Position.cpp.i

CMakeFiles/Chess.dir/Position.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/Position.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas/CLionProjects/Chess/Position.cpp -o CMakeFiles/Chess.dir/Position.cpp.s

CMakeFiles/Chess.dir/Move.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/Move.cpp.o: ../Move.cpp
CMakeFiles/Chess.dir/Move.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas/CLionProjects/Chess/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Chess.dir/Move.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/Move.cpp.o -MF CMakeFiles/Chess.dir/Move.cpp.o.d -o CMakeFiles/Chess.dir/Move.cpp.o -c /home/thomas/CLionProjects/Chess/Move.cpp

CMakeFiles/Chess.dir/Move.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/Move.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomas/CLionProjects/Chess/Move.cpp > CMakeFiles/Chess.dir/Move.cpp.i

CMakeFiles/Chess.dir/Move.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/Move.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomas/CLionProjects/Chess/Move.cpp -o CMakeFiles/Chess.dir/Move.cpp.s

# Object files for target Chess
Chess_OBJECTS = \
"CMakeFiles/Chess.dir/main.cpp.o" \
"CMakeFiles/Chess.dir/Position.cpp.o" \
"CMakeFiles/Chess.dir/Move.cpp.o"

# External object files for target Chess
Chess_EXTERNAL_OBJECTS =

Chess: CMakeFiles/Chess.dir/main.cpp.o
Chess: CMakeFiles/Chess.dir/Position.cpp.o
Chess: CMakeFiles/Chess.dir/Move.cpp.o
Chess: CMakeFiles/Chess.dir/build.make
Chess: CMakeFiles/Chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thomas/CLionProjects/Chess/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Chess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chess.dir/build: Chess
.PHONY : CMakeFiles/Chess.dir/build

CMakeFiles/Chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Chess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Chess.dir/clean

CMakeFiles/Chess.dir/depend:
	cd /home/thomas/CLionProjects/Chess/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas/CLionProjects/Chess /home/thomas/CLionProjects/Chess /home/thomas/CLionProjects/Chess/cmake-build-debug /home/thomas/CLionProjects/Chess/cmake-build-debug /home/thomas/CLionProjects/Chess/cmake-build-debug/CMakeFiles/Chess.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Chess.dir/depend
