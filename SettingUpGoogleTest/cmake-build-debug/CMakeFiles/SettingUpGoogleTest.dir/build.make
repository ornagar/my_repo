# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/xyz/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/xyz/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xyz/my_repo/my_repo/SettingUpGoogleTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SettingUpGoogleTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SettingUpGoogleTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SettingUpGoogleTest.dir/flags.make

CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o: CMakeFiles/SettingUpGoogleTest.dir/flags.make
CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o -c /home/xyz/my_repo/my_repo/SettingUpGoogleTest/main.cpp

CMakeFiles/SettingUpGoogleTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SettingUpGoogleTest.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xyz/my_repo/my_repo/SettingUpGoogleTest/main.cpp > CMakeFiles/SettingUpGoogleTest.dir/main.cpp.i

CMakeFiles/SettingUpGoogleTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SettingUpGoogleTest.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xyz/my_repo/my_repo/SettingUpGoogleTest/main.cpp -o CMakeFiles/SettingUpGoogleTest.dir/main.cpp.s

CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.requires

CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.provides: CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SettingUpGoogleTest.dir/build.make CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.provides

CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.provides.build: CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o


CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o: CMakeFiles/SettingUpGoogleTest.dir/flags.make
CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o: ../tests/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o -c /home/xyz/my_repo/my_repo/SettingUpGoogleTest/tests/test.cpp

CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xyz/my_repo/my_repo/SettingUpGoogleTest/tests/test.cpp > CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.i

CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xyz/my_repo/my_repo/SettingUpGoogleTest/tests/test.cpp -o CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.s

CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.requires:

.PHONY : CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.requires

CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.provides: CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/SettingUpGoogleTest.dir/build.make CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.provides.build
.PHONY : CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.provides

CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.provides.build: CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o


# Object files for target SettingUpGoogleTest
SettingUpGoogleTest_OBJECTS = \
"CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o" \
"CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o"

# External object files for target SettingUpGoogleTest
SettingUpGoogleTest_EXTERNAL_OBJECTS =

SettingUpGoogleTest: CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o
SettingUpGoogleTest: CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o
SettingUpGoogleTest: CMakeFiles/SettingUpGoogleTest.dir/build.make
SettingUpGoogleTest: lib/googletest/googlemock/gtest/libgtestd.a
SettingUpGoogleTest: lib/googletest/googlemock/gtest/libgtest_maind.a
SettingUpGoogleTest: lib/googletest/googlemock/gtest/libgtestd.a
SettingUpGoogleTest: CMakeFiles/SettingUpGoogleTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SettingUpGoogleTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SettingUpGoogleTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SettingUpGoogleTest.dir/build: SettingUpGoogleTest

.PHONY : CMakeFiles/SettingUpGoogleTest.dir/build

CMakeFiles/SettingUpGoogleTest.dir/requires: CMakeFiles/SettingUpGoogleTest.dir/main.cpp.o.requires
CMakeFiles/SettingUpGoogleTest.dir/requires: CMakeFiles/SettingUpGoogleTest.dir/tests/test.cpp.o.requires

.PHONY : CMakeFiles/SettingUpGoogleTest.dir/requires

CMakeFiles/SettingUpGoogleTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SettingUpGoogleTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SettingUpGoogleTest.dir/clean

CMakeFiles/SettingUpGoogleTest.dir/depend:
	cd /home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xyz/my_repo/my_repo/SettingUpGoogleTest /home/xyz/my_repo/my_repo/SettingUpGoogleTest /home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug /home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug /home/xyz/my_repo/my_repo/SettingUpGoogleTest/cmake-build-debug/CMakeFiles/SettingUpGoogleTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SettingUpGoogleTest.dir/depend
