# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Sascha/projects/Tamara

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Sascha/projects/Tamara

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest.exe --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/Sascha/projects/Tamara/CMakeFiles /home/Sascha/projects/Tamara/CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/Sascha/projects/Tamara/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tamara

# Build rule for target.
tamara: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 tamara
.PHONY : tamara

# fast build rule for target.
tamara/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/build
.PHONY : tamara/fast

packages/src/Curl.o: packages/src/Curl.c.o

.PHONY : packages/src/Curl.o

# target to build an object file
packages/src/Curl.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/Curl.c.o
.PHONY : packages/src/Curl.c.o

packages/src/Curl.i: packages/src/Curl.c.i

.PHONY : packages/src/Curl.i

# target to preprocess a source file
packages/src/Curl.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/Curl.c.i
.PHONY : packages/src/Curl.c.i

packages/src/Curl.s: packages/src/Curl.c.s

.PHONY : packages/src/Curl.s

# target to generate assembly for a file
packages/src/Curl.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/Curl.c.s
.PHONY : packages/src/Curl.c.s

packages/src/File.o: packages/src/File.c.o

.PHONY : packages/src/File.o

# target to build an object file
packages/src/File.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/File.c.o
.PHONY : packages/src/File.c.o

packages/src/File.i: packages/src/File.c.i

.PHONY : packages/src/File.i

# target to preprocess a source file
packages/src/File.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/File.c.i
.PHONY : packages/src/File.c.i

packages/src/File.s: packages/src/File.c.s

.PHONY : packages/src/File.s

# target to generate assembly for a file
packages/src/File.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/File.c.s
.PHONY : packages/src/File.c.s

packages/src/Maths.o: packages/src/Maths.c.o

.PHONY : packages/src/Maths.o

# target to build an object file
packages/src/Maths.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/Maths.c.o
.PHONY : packages/src/Maths.c.o

packages/src/Maths.i: packages/src/Maths.c.i

.PHONY : packages/src/Maths.i

# target to preprocess a source file
packages/src/Maths.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/Maths.c.i
.PHONY : packages/src/Maths.c.i

packages/src/Maths.s: packages/src/Maths.c.s

.PHONY : packages/src/Maths.s

# target to generate assembly for a file
packages/src/Maths.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/Maths.c.s
.PHONY : packages/src/Maths.c.s

packages/src/System.o: packages/src/System.c.o

.PHONY : packages/src/System.o

# target to build an object file
packages/src/System.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/System.c.o
.PHONY : packages/src/System.c.o

packages/src/System.i: packages/src/System.c.i

.PHONY : packages/src/System.i

# target to preprocess a source file
packages/src/System.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/System.c.i
.PHONY : packages/src/System.c.i

packages/src/System.s: packages/src/System.c.s

.PHONY : packages/src/System.s

# target to generate assembly for a file
packages/src/System.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/packages/src/System.c.s
.PHONY : packages/src/System.c.s

src/Builtins.o: src/Builtins.c.o

.PHONY : src/Builtins.o

# target to build an object file
src/Builtins.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Builtins.c.o
.PHONY : src/Builtins.c.o

src/Builtins.i: src/Builtins.c.i

.PHONY : src/Builtins.i

# target to preprocess a source file
src/Builtins.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Builtins.c.i
.PHONY : src/Builtins.c.i

src/Builtins.s: src/Builtins.c.s

.PHONY : src/Builtins.s

# target to generate assembly for a file
src/Builtins.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Builtins.c.s
.PHONY : src/Builtins.c.s

src/Environment.o: src/Environment.c.o

.PHONY : src/Environment.o

# target to build an object file
src/Environment.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Environment.c.o
.PHONY : src/Environment.c.o

src/Environment.i: src/Environment.c.i

.PHONY : src/Environment.i

# target to preprocess a source file
src/Environment.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Environment.c.i
.PHONY : src/Environment.c.i

src/Environment.s: src/Environment.c.s

.PHONY : src/Environment.s

# target to generate assembly for a file
src/Environment.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Environment.c.s
.PHONY : src/Environment.c.s

src/Environment_packages.o: src/Environment_packages.c.o

.PHONY : src/Environment_packages.o

# target to build an object file
src/Environment_packages.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Environment_packages.c.o
.PHONY : src/Environment_packages.c.o

src/Environment_packages.i: src/Environment_packages.c.i

.PHONY : src/Environment_packages.i

# target to preprocess a source file
src/Environment_packages.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Environment_packages.c.i
.PHONY : src/Environment_packages.c.i

src/Environment_packages.s: src/Environment_packages.c.s

.PHONY : src/Environment_packages.s

# target to generate assembly for a file
src/Environment_packages.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Environment_packages.c.s
.PHONY : src/Environment_packages.c.s

src/Lval.o: src/Lval.c.o

.PHONY : src/Lval.o

# target to build an object file
src/Lval.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Lval.c.o
.PHONY : src/Lval.c.o

src/Lval.i: src/Lval.c.i

.PHONY : src/Lval.i

# target to preprocess a source file
src/Lval.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Lval.c.i
.PHONY : src/Lval.c.i

src/Lval.s: src/Lval.c.s

.PHONY : src/Lval.s

# target to generate assembly for a file
src/Lval.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/Lval.c.s
.PHONY : src/Lval.c.s

src/ParserDefinition.o: src/ParserDefinition.c.o

.PHONY : src/ParserDefinition.o

# target to build an object file
src/ParserDefinition.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/ParserDefinition.c.o
.PHONY : src/ParserDefinition.c.o

src/ParserDefinition.i: src/ParserDefinition.c.i

.PHONY : src/ParserDefinition.i

# target to preprocess a source file
src/ParserDefinition.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/ParserDefinition.c.i
.PHONY : src/ParserDefinition.c.i

src/ParserDefinition.s: src/ParserDefinition.c.s

.PHONY : src/ParserDefinition.s

# target to generate assembly for a file
src/ParserDefinition.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/ParserDefinition.c.s
.PHONY : src/ParserDefinition.c.s

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/main.c.s
.PHONY : src/main.c.s

src/mpc.o: src/mpc.c.o

.PHONY : src/mpc.o

# target to build an object file
src/mpc.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/mpc.c.o
.PHONY : src/mpc.c.o

src/mpc.i: src/mpc.c.i

.PHONY : src/mpc.i

# target to preprocess a source file
src/mpc.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/mpc.c.i
.PHONY : src/mpc.c.i

src/mpc.s: src/mpc.c.s

.PHONY : src/mpc.s

# target to generate assembly for a file
src/mpc.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tamara.dir/build.make CMakeFiles/tamara.dir/src/mpc.c.s
.PHONY : src/mpc.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... tamara"
	@echo "... packages/src/Curl.o"
	@echo "... packages/src/Curl.i"
	@echo "... packages/src/Curl.s"
	@echo "... packages/src/File.o"
	@echo "... packages/src/File.i"
	@echo "... packages/src/File.s"
	@echo "... packages/src/Maths.o"
	@echo "... packages/src/Maths.i"
	@echo "... packages/src/Maths.s"
	@echo "... packages/src/System.o"
	@echo "... packages/src/System.i"
	@echo "... packages/src/System.s"
	@echo "... src/Builtins.o"
	@echo "... src/Builtins.i"
	@echo "... src/Builtins.s"
	@echo "... src/Environment.o"
	@echo "... src/Environment.i"
	@echo "... src/Environment.s"
	@echo "... src/Environment_packages.o"
	@echo "... src/Environment_packages.i"
	@echo "... src/Environment_packages.s"
	@echo "... src/Lval.o"
	@echo "... src/Lval.i"
	@echo "... src/Lval.s"
	@echo "... src/ParserDefinition.o"
	@echo "... src/ParserDefinition.i"
	@echo "... src/ParserDefinition.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/mpc.o"
	@echo "... src/mpc.i"
	@echo "... src/mpc.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

