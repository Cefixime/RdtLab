# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/wei/workspace/NetWorkLab/RdtLab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wei/workspace/NetWorkLab/RdtLab/build

# Include any dependencies generated for this target.
include CMakeFiles/stop_wait.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stop_wait.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stop_wait.dir/flags.make

CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o: CMakeFiles/stop_wait.dir/flags.make
CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o: ../src/SW/StopWait.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wei/workspace/NetWorkLab/RdtLab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o"
	/usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o -c /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWait.cpp

CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.i"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWait.cpp > CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.i

CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.s"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWait.cpp -o CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.s

CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.requires:

.PHONY : CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.requires

CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.provides: CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.requires
	$(MAKE) -f CMakeFiles/stop_wait.dir/build.make CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.provides.build
.PHONY : CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.provides

CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.provides.build: CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o


CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o: CMakeFiles/stop_wait.dir/flags.make
CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o: ../src/SW/StopWaitRdtReceiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wei/workspace/NetWorkLab/RdtLab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o"
	/usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o -c /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWaitRdtReceiver.cpp

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.i"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWaitRdtReceiver.cpp > CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.i

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.s"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWaitRdtReceiver.cpp -o CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.s

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.requires:

.PHONY : CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.requires

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.provides: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.requires
	$(MAKE) -f CMakeFiles/stop_wait.dir/build.make CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.provides.build
.PHONY : CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.provides

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.provides.build: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o


CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o: CMakeFiles/stop_wait.dir/flags.make
CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o: ../src/SW/StopWaitRdtSender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wei/workspace/NetWorkLab/RdtLab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o"
	/usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o -c /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWaitRdtSender.cpp

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.i"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWaitRdtSender.cpp > CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.i

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.s"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wei/workspace/NetWorkLab/RdtLab/src/SW/StopWaitRdtSender.cpp -o CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.s

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.requires:

.PHONY : CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.requires

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.provides: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.requires
	$(MAKE) -f CMakeFiles/stop_wait.dir/build.make CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.provides.build
.PHONY : CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.provides

CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.provides.build: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o


# Object files for target stop_wait
stop_wait_OBJECTS = \
"CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o" \
"CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o" \
"CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o"

# External object files for target stop_wait
stop_wait_EXTERNAL_OBJECTS =

../bin/stop_wait: CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o
../bin/stop_wait: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o
../bin/stop_wait: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o
../bin/stop_wait: CMakeFiles/stop_wait.dir/build.make
../bin/stop_wait: ../lib/libnetsim.a
../bin/stop_wait: CMakeFiles/stop_wait.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wei/workspace/NetWorkLab/RdtLab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/stop_wait"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stop_wait.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stop_wait.dir/build: ../bin/stop_wait

.PHONY : CMakeFiles/stop_wait.dir/build

CMakeFiles/stop_wait.dir/requires: CMakeFiles/stop_wait.dir/src/SW/StopWait.cpp.o.requires
CMakeFiles/stop_wait.dir/requires: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtReceiver.cpp.o.requires
CMakeFiles/stop_wait.dir/requires: CMakeFiles/stop_wait.dir/src/SW/StopWaitRdtSender.cpp.o.requires

.PHONY : CMakeFiles/stop_wait.dir/requires

CMakeFiles/stop_wait.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stop_wait.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stop_wait.dir/clean

CMakeFiles/stop_wait.dir/depend:
	cd /home/wei/workspace/NetWorkLab/RdtLab/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wei/workspace/NetWorkLab/RdtLab /home/wei/workspace/NetWorkLab/RdtLab /home/wei/workspace/NetWorkLab/RdtLab/build /home/wei/workspace/NetWorkLab/RdtLab/build /home/wei/workspace/NetWorkLab/RdtLab/build/CMakeFiles/stop_wait.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stop_wait.dir/depend
