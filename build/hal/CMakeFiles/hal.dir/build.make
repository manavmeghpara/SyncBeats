# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/danieva/cmpt433/work/project/SyncBeats

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danieva/cmpt433/work/project/SyncBeats/build

# Include any dependencies generated for this target.
include hal/CMakeFiles/hal.dir/depend.make

# Include the progress variables for this target.
include hal/CMakeFiles/hal.dir/progress.make

# Include the compile flags for this target's objects.
include hal/CMakeFiles/hal.dir/flags.make

hal/CMakeFiles/hal.dir/src/ble.c.o: hal/CMakeFiles/hal.dir/flags.make
hal/CMakeFiles/hal.dir/src/ble.c.o: ../hal/src/ble.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danieva/cmpt433/work/project/SyncBeats/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object hal/CMakeFiles/hal.dir/src/ble.c.o"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hal.dir/src/ble.c.o -c /home/danieva/cmpt433/work/project/SyncBeats/hal/src/ble.c

hal/CMakeFiles/hal.dir/src/ble.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hal.dir/src/ble.c.i"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danieva/cmpt433/work/project/SyncBeats/hal/src/ble.c > CMakeFiles/hal.dir/src/ble.c.i

hal/CMakeFiles/hal.dir/src/ble.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hal.dir/src/ble.c.s"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danieva/cmpt433/work/project/SyncBeats/hal/src/ble.c -o CMakeFiles/hal.dir/src/ble.c.s

hal/CMakeFiles/hal.dir/src/spi.c.o: hal/CMakeFiles/hal.dir/flags.make
hal/CMakeFiles/hal.dir/src/spi.c.o: ../hal/src/spi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danieva/cmpt433/work/project/SyncBeats/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object hal/CMakeFiles/hal.dir/src/spi.c.o"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hal.dir/src/spi.c.o -c /home/danieva/cmpt433/work/project/SyncBeats/hal/src/spi.c

hal/CMakeFiles/hal.dir/src/spi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hal.dir/src/spi.c.i"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danieva/cmpt433/work/project/SyncBeats/hal/src/spi.c > CMakeFiles/hal.dir/src/spi.c.i

hal/CMakeFiles/hal.dir/src/spi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hal.dir/src/spi.c.s"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danieva/cmpt433/work/project/SyncBeats/hal/src/spi.c -o CMakeFiles/hal.dir/src/spi.c.s

hal/CMakeFiles/hal.dir/src/system.c.o: hal/CMakeFiles/hal.dir/flags.make
hal/CMakeFiles/hal.dir/src/system.c.o: ../hal/src/system.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danieva/cmpt433/work/project/SyncBeats/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object hal/CMakeFiles/hal.dir/src/system.c.o"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hal.dir/src/system.c.o -c /home/danieva/cmpt433/work/project/SyncBeats/hal/src/system.c

hal/CMakeFiles/hal.dir/src/system.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hal.dir/src/system.c.i"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danieva/cmpt433/work/project/SyncBeats/hal/src/system.c > CMakeFiles/hal.dir/src/system.c.i

hal/CMakeFiles/hal.dir/src/system.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hal.dir/src/system.c.s"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danieva/cmpt433/work/project/SyncBeats/hal/src/system.c -o CMakeFiles/hal.dir/src/system.c.s

hal/CMakeFiles/hal.dir/src/uart.c.o: hal/CMakeFiles/hal.dir/flags.make
hal/CMakeFiles/hal.dir/src/uart.c.o: ../hal/src/uart.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danieva/cmpt433/work/project/SyncBeats/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object hal/CMakeFiles/hal.dir/src/uart.c.o"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hal.dir/src/uart.c.o -c /home/danieva/cmpt433/work/project/SyncBeats/hal/src/uart.c

hal/CMakeFiles/hal.dir/src/uart.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hal.dir/src/uart.c.i"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danieva/cmpt433/work/project/SyncBeats/hal/src/uart.c > CMakeFiles/hal.dir/src/uart.c.i

hal/CMakeFiles/hal.dir/src/uart.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hal.dir/src/uart.c.s"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danieva/cmpt433/work/project/SyncBeats/hal/src/uart.c -o CMakeFiles/hal.dir/src/uart.c.s

# Object files for target hal
hal_OBJECTS = \
"CMakeFiles/hal.dir/src/ble.c.o" \
"CMakeFiles/hal.dir/src/spi.c.o" \
"CMakeFiles/hal.dir/src/system.c.o" \
"CMakeFiles/hal.dir/src/uart.c.o"

# External object files for target hal
hal_EXTERNAL_OBJECTS =

hal/libhal.a: hal/CMakeFiles/hal.dir/src/ble.c.o
hal/libhal.a: hal/CMakeFiles/hal.dir/src/spi.c.o
hal/libhal.a: hal/CMakeFiles/hal.dir/src/system.c.o
hal/libhal.a: hal/CMakeFiles/hal.dir/src/uart.c.o
hal/libhal.a: hal/CMakeFiles/hal.dir/build.make
hal/libhal.a: hal/CMakeFiles/hal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danieva/cmpt433/work/project/SyncBeats/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libhal.a"
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && $(CMAKE_COMMAND) -P CMakeFiles/hal.dir/cmake_clean_target.cmake
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hal/CMakeFiles/hal.dir/build: hal/libhal.a

.PHONY : hal/CMakeFiles/hal.dir/build

hal/CMakeFiles/hal.dir/clean:
	cd /home/danieva/cmpt433/work/project/SyncBeats/build/hal && $(CMAKE_COMMAND) -P CMakeFiles/hal.dir/cmake_clean.cmake
.PHONY : hal/CMakeFiles/hal.dir/clean

hal/CMakeFiles/hal.dir/depend:
	cd /home/danieva/cmpt433/work/project/SyncBeats/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danieva/cmpt433/work/project/SyncBeats /home/danieva/cmpt433/work/project/SyncBeats/hal /home/danieva/cmpt433/work/project/SyncBeats/build /home/danieva/cmpt433/work/project/SyncBeats/build/hal /home/danieva/cmpt433/work/project/SyncBeats/build/hal/CMakeFiles/hal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hal/CMakeFiles/hal.dir/depend

