# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/randolph/Develop/cmake_rv/sMPI/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/randolph/Develop/cmake_rv/sMPI/build

# Include any dependencies generated for this target.
include CMakeFiles/sMPI.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sMPI.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sMPI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sMPI.dir/flags.make

CMakeFiles/sMPI.dir/start.S.obj: CMakeFiles/sMPI.dir/flags.make
CMakeFiles/sMPI.dir/start.S.obj: /home/randolph/Develop/cmake_rv/sMPI/src/start.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/randolph/Develop/cmake_rv/sMPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object CMakeFiles/sMPI.dir/start.S.obj"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/sMPI.dir/start.S.obj -c /home/randolph/Develop/cmake_rv/sMPI/src/start.S

CMakeFiles/sMPI.dir/start.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/sMPI.dir/start.S.i"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/randolph/Develop/cmake_rv/sMPI/src/start.S > CMakeFiles/sMPI.dir/start.S.i

CMakeFiles/sMPI.dir/start.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/sMPI.dir/start.S.s"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/randolph/Develop/cmake_rv/sMPI/src/start.S -o CMakeFiles/sMPI.dir/start.S.s

CMakeFiles/sMPI.dir/main.c.obj: CMakeFiles/sMPI.dir/flags.make
CMakeFiles/sMPI.dir/main.c.obj: /home/randolph/Develop/cmake_rv/sMPI/src/main.c
CMakeFiles/sMPI.dir/main.c.obj: CMakeFiles/sMPI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/randolph/Develop/cmake_rv/sMPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/sMPI.dir/main.c.obj"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/sMPI.dir/main.c.obj -MF CMakeFiles/sMPI.dir/main.c.obj.d -o CMakeFiles/sMPI.dir/main.c.obj -c /home/randolph/Develop/cmake_rv/sMPI/src/main.c

CMakeFiles/sMPI.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sMPI.dir/main.c.i"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/randolph/Develop/cmake_rv/sMPI/src/main.c > CMakeFiles/sMPI.dir/main.c.i

CMakeFiles/sMPI.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sMPI.dir/main.c.s"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/randolph/Develop/cmake_rv/sMPI/src/main.c -o CMakeFiles/sMPI.dir/main.c.s

CMakeFiles/sMPI.dir/common.c.obj: CMakeFiles/sMPI.dir/flags.make
CMakeFiles/sMPI.dir/common.c.obj: /home/randolph/Develop/cmake_rv/sMPI/src/common.c
CMakeFiles/sMPI.dir/common.c.obj: CMakeFiles/sMPI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/randolph/Develop/cmake_rv/sMPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/sMPI.dir/common.c.obj"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/sMPI.dir/common.c.obj -MF CMakeFiles/sMPI.dir/common.c.obj.d -o CMakeFiles/sMPI.dir/common.c.obj -c /home/randolph/Develop/cmake_rv/sMPI/src/common.c

CMakeFiles/sMPI.dir/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sMPI.dir/common.c.i"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/randolph/Develop/cmake_rv/sMPI/src/common.c > CMakeFiles/sMPI.dir/common.c.i

CMakeFiles/sMPI.dir/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sMPI.dir/common.c.s"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/randolph/Develop/cmake_rv/sMPI/src/common.c -o CMakeFiles/sMPI.dir/common.c.s

CMakeFiles/sMPI.dir/intc.c.obj: CMakeFiles/sMPI.dir/flags.make
CMakeFiles/sMPI.dir/intc.c.obj: /home/randolph/Develop/cmake_rv/sMPI/src/intc.c
CMakeFiles/sMPI.dir/intc.c.obj: CMakeFiles/sMPI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/randolph/Develop/cmake_rv/sMPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/sMPI.dir/intc.c.obj"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/sMPI.dir/intc.c.obj -MF CMakeFiles/sMPI.dir/intc.c.obj.d -o CMakeFiles/sMPI.dir/intc.c.obj -c /home/randolph/Develop/cmake_rv/sMPI/src/intc.c

CMakeFiles/sMPI.dir/intc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sMPI.dir/intc.c.i"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/randolph/Develop/cmake_rv/sMPI/src/intc.c > CMakeFiles/sMPI.dir/intc.c.i

CMakeFiles/sMPI.dir/intc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sMPI.dir/intc.c.s"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/randolph/Develop/cmake_rv/sMPI/src/intc.c -o CMakeFiles/sMPI.dir/intc.c.s

CMakeFiles/sMPI.dir/sMPI.c.obj: CMakeFiles/sMPI.dir/flags.make
CMakeFiles/sMPI.dir/sMPI.c.obj: /home/randolph/Develop/cmake_rv/sMPI/src/sMPI.c
CMakeFiles/sMPI.dir/sMPI.c.obj: CMakeFiles/sMPI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/randolph/Develop/cmake_rv/sMPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/sMPI.dir/sMPI.c.obj"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/sMPI.dir/sMPI.c.obj -MF CMakeFiles/sMPI.dir/sMPI.c.obj.d -o CMakeFiles/sMPI.dir/sMPI.c.obj -c /home/randolph/Develop/cmake_rv/sMPI/src/sMPI.c

CMakeFiles/sMPI.dir/sMPI.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sMPI.dir/sMPI.c.i"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/randolph/Develop/cmake_rv/sMPI/src/sMPI.c > CMakeFiles/sMPI.dir/sMPI.c.i

CMakeFiles/sMPI.dir/sMPI.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sMPI.dir/sMPI.c.s"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/randolph/Develop/cmake_rv/sMPI/src/sMPI.c -o CMakeFiles/sMPI.dir/sMPI.c.s

# Object files for target sMPI
sMPI_OBJECTS = \
"CMakeFiles/sMPI.dir/start.S.obj" \
"CMakeFiles/sMPI.dir/main.c.obj" \
"CMakeFiles/sMPI.dir/common.c.obj" \
"CMakeFiles/sMPI.dir/intc.c.obj" \
"CMakeFiles/sMPI.dir/sMPI.c.obj"

# External object files for target sMPI
sMPI_EXTERNAL_OBJECTS =

sMPI: CMakeFiles/sMPI.dir/start.S.obj
sMPI: CMakeFiles/sMPI.dir/main.c.obj
sMPI: CMakeFiles/sMPI.dir/common.c.obj
sMPI: CMakeFiles/sMPI.dir/intc.c.obj
sMPI: CMakeFiles/sMPI.dir/sMPI.c.obj
sMPI: CMakeFiles/sMPI.dir/build.make
sMPI: CMakeFiles/sMPI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/randolph/Develop/cmake_rv/sMPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable sMPI"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sMPI.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Creating sMPI.hex file"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-objcopy -g -O verilog sMPI sMPI.hex
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Creating sMPI.bin file"
	/home/randolph/Develop/cmake_rv/bin/riscv32-unknown-elf-objcopy -O binary sMPI sMPI.bin
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Creating sMPI.map file"

# Rule to build all files generated by this target.
CMakeFiles/sMPI.dir/build: sMPI
.PHONY : CMakeFiles/sMPI.dir/build

CMakeFiles/sMPI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sMPI.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sMPI.dir/clean

CMakeFiles/sMPI.dir/depend:
	cd /home/randolph/Develop/cmake_rv/sMPI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/randolph/Develop/cmake_rv/sMPI/src /home/randolph/Develop/cmake_rv/sMPI/src /home/randolph/Develop/cmake_rv/sMPI/build /home/randolph/Develop/cmake_rv/sMPI/build /home/randolph/Develop/cmake_rv/sMPI/build/CMakeFiles/sMPI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sMPI.dir/depend
