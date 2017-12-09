# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robotics/cpp/mamdany

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robotics/cpp/mamdany/build-mytoolchain

# Include any dependencies generated for this target.
include CMakeFiles/mamdany.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mamdany.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mamdany.dir/flags.make

CMakeFiles/mamdany.dir/main.cpp.o: CMakeFiles/mamdany.dir/flags.make
CMakeFiles/mamdany.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robotics/cpp/mamdany/build-mytoolchain/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mamdany.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mamdany.dir/main.cpp.o -c /home/robotics/cpp/mamdany/main.cpp

CMakeFiles/mamdany.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mamdany.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robotics/cpp/mamdany/main.cpp > CMakeFiles/mamdany.dir/main.cpp.i

CMakeFiles/mamdany.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mamdany.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robotics/cpp/mamdany/main.cpp -o CMakeFiles/mamdany.dir/main.cpp.s

CMakeFiles/mamdany.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/mamdany.dir/main.cpp.o.requires

CMakeFiles/mamdany.dir/main.cpp.o.provides: CMakeFiles/mamdany.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mamdany.dir/build.make CMakeFiles/mamdany.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mamdany.dir/main.cpp.o.provides

CMakeFiles/mamdany.dir/main.cpp.o.provides.build: CMakeFiles/mamdany.dir/main.cpp.o

# Object files for target mamdany
mamdany_OBJECTS = \
"CMakeFiles/mamdany.dir/main.cpp.o"

# External object files for target mamdany
mamdany_EXTERNAL_OBJECTS =

sdk/bin/mamdany: CMakeFiles/mamdany.dir/main.cpp.o
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalvision.so
sdk/bin/mamdany: /usr/local/lib/libopencv_core.so
sdk/bin/mamdany: /usr/local/lib/libopencv_highgui.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalextractor.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalproxies.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalproxies.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalcommon.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalsoap.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/librttools.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalthread.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libboost_signals-mt.a
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libboost_program_options-mt.a
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalvalue.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libtinyxml.so
sdk/bin/mamdany: /usr/lib/i386-linux-gnu/librt.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libqi.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libboost_filesystem-mt.a
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libboost_thread-mt.a
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libboost_system-mt.a
sdk/bin/mamdany: /usr/lib/i386-linux-gnu/libdl.so
sdk/bin/mamdany: /home/robotics/naoqi-sdk-1.14.3-linux32/lib/libalerror.so
sdk/bin/mamdany: CMakeFiles/mamdany.dir/build.make
sdk/bin/mamdany: CMakeFiles/mamdany.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sdk/bin/mamdany"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mamdany.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mamdany.dir/build: sdk/bin/mamdany
.PHONY : CMakeFiles/mamdany.dir/build

CMakeFiles/mamdany.dir/requires: CMakeFiles/mamdany.dir/main.cpp.o.requires
.PHONY : CMakeFiles/mamdany.dir/requires

CMakeFiles/mamdany.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mamdany.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mamdany.dir/clean

CMakeFiles/mamdany.dir/depend:
	cd /home/robotics/cpp/mamdany/build-mytoolchain && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robotics/cpp/mamdany /home/robotics/cpp/mamdany /home/robotics/cpp/mamdany/build-mytoolchain /home/robotics/cpp/mamdany/build-mytoolchain /home/robotics/cpp/mamdany/build-mytoolchain/CMakeFiles/mamdany.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mamdany.dir/depend

