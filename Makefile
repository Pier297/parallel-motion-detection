# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/p.tarasco/parallel-motion-detection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/p.tarasco/parallel-motion-detection

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/p.tarasco/parallel-motion-detection/CMakeFiles /home/p.tarasco/parallel-motion-detection/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/p.tarasco/parallel-motion-detection/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Blur

# Build rule for target.
Blur: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Blur
.PHONY : Blur

# fast build rule for target.
Blur/fast:
	$(MAKE) -f CMakeFiles/Blur.dir/build.make CMakeFiles/Blur.dir/build
.PHONY : Blur/fast

#=============================================================================
# Target rules for targets named Main

# Build rule for target.
Main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Main
.PHONY : Main

# fast build rule for target.
Main/fast:
	$(MAKE) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/build
.PHONY : Main/fast

#=============================================================================
# Target rules for targets named Grayscale

# Build rule for target.
Grayscale: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Grayscale
.PHONY : Grayscale

# fast build rule for target.
Grayscale/fast:
	$(MAKE) -f CMakeFiles/Grayscale.dir/build.make CMakeFiles/Grayscale.dir/build
.PHONY : Grayscale/fast

#=============================================================================
# Target rules for targets named Benchmark

# Build rule for target.
Benchmark: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Benchmark
.PHONY : Benchmark

# fast build rule for target.
Benchmark/fast:
	$(MAKE) -f CMakeFiles/Benchmark.dir/build.make CMakeFiles/Benchmark.dir/build
.PHONY : Benchmark/fast

#=============================================================================
# Target rules for targets named Check

# Build rule for target.
Check: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Check
.PHONY : Check

# fast build rule for target.
Check/fast:
	$(MAKE) -f CMakeFiles/Check.dir/build.make CMakeFiles/Check.dir/build
.PHONY : Check/fast

#=============================================================================
# Target rules for targets named OptBlur

# Build rule for target.
OptBlur: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 OptBlur
.PHONY : OptBlur

# fast build rule for target.
OptBlur/fast:
	$(MAKE) -f CMakeFiles/OptBlur.dir/build.make CMakeFiles/OptBlur.dir/build
.PHONY : OptBlur/fast

#=============================================================================
# Target rules for targets named Read

# Build rule for target.
Read: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Read
.PHONY : Read

# fast build rule for target.
Read/fast:
	$(MAKE) -f CMakeFiles/Read.dir/build.make CMakeFiles/Read.dir/build
.PHONY : Read/fast

experiments/Blur.o: experiments/Blur.cpp.o

.PHONY : experiments/Blur.o

# target to build an object file
experiments/Blur.cpp.o:
	$(MAKE) -f CMakeFiles/Blur.dir/build.make CMakeFiles/Blur.dir/experiments/Blur.cpp.o
.PHONY : experiments/Blur.cpp.o

experiments/Blur.i: experiments/Blur.cpp.i

.PHONY : experiments/Blur.i

# target to preprocess a source file
experiments/Blur.cpp.i:
	$(MAKE) -f CMakeFiles/Blur.dir/build.make CMakeFiles/Blur.dir/experiments/Blur.cpp.i
.PHONY : experiments/Blur.cpp.i

experiments/Blur.s: experiments/Blur.cpp.s

.PHONY : experiments/Blur.s

# target to generate assembly for a file
experiments/Blur.cpp.s:
	$(MAKE) -f CMakeFiles/Blur.dir/build.make CMakeFiles/Blur.dir/experiments/Blur.cpp.s
.PHONY : experiments/Blur.cpp.s

experiments/Check.o: experiments/Check.cpp.o

.PHONY : experiments/Check.o

# target to build an object file
experiments/Check.cpp.o:
	$(MAKE) -f CMakeFiles/Check.dir/build.make CMakeFiles/Check.dir/experiments/Check.cpp.o
.PHONY : experiments/Check.cpp.o

experiments/Check.i: experiments/Check.cpp.i

.PHONY : experiments/Check.i

# target to preprocess a source file
experiments/Check.cpp.i:
	$(MAKE) -f CMakeFiles/Check.dir/build.make CMakeFiles/Check.dir/experiments/Check.cpp.i
.PHONY : experiments/Check.cpp.i

experiments/Check.s: experiments/Check.cpp.s

.PHONY : experiments/Check.s

# target to generate assembly for a file
experiments/Check.cpp.s:
	$(MAKE) -f CMakeFiles/Check.dir/build.make CMakeFiles/Check.dir/experiments/Check.cpp.s
.PHONY : experiments/Check.cpp.s

experiments/Grayscale.o: experiments/Grayscale.cpp.o

.PHONY : experiments/Grayscale.o

# target to build an object file
experiments/Grayscale.cpp.o:
	$(MAKE) -f CMakeFiles/Grayscale.dir/build.make CMakeFiles/Grayscale.dir/experiments/Grayscale.cpp.o
.PHONY : experiments/Grayscale.cpp.o

experiments/Grayscale.i: experiments/Grayscale.cpp.i

.PHONY : experiments/Grayscale.i

# target to preprocess a source file
experiments/Grayscale.cpp.i:
	$(MAKE) -f CMakeFiles/Grayscale.dir/build.make CMakeFiles/Grayscale.dir/experiments/Grayscale.cpp.i
.PHONY : experiments/Grayscale.cpp.i

experiments/Grayscale.s: experiments/Grayscale.cpp.s

.PHONY : experiments/Grayscale.s

# target to generate assembly for a file
experiments/Grayscale.cpp.s:
	$(MAKE) -f CMakeFiles/Grayscale.dir/build.make CMakeFiles/Grayscale.dir/experiments/Grayscale.cpp.s
.PHONY : experiments/Grayscale.cpp.s

experiments/OptBlur.o: experiments/OptBlur.cpp.o

.PHONY : experiments/OptBlur.o

# target to build an object file
experiments/OptBlur.cpp.o:
	$(MAKE) -f CMakeFiles/OptBlur.dir/build.make CMakeFiles/OptBlur.dir/experiments/OptBlur.cpp.o
.PHONY : experiments/OptBlur.cpp.o

experiments/OptBlur.i: experiments/OptBlur.cpp.i

.PHONY : experiments/OptBlur.i

# target to preprocess a source file
experiments/OptBlur.cpp.i:
	$(MAKE) -f CMakeFiles/OptBlur.dir/build.make CMakeFiles/OptBlur.dir/experiments/OptBlur.cpp.i
.PHONY : experiments/OptBlur.cpp.i

experiments/OptBlur.s: experiments/OptBlur.cpp.s

.PHONY : experiments/OptBlur.s

# target to generate assembly for a file
experiments/OptBlur.cpp.s:
	$(MAKE) -f CMakeFiles/OptBlur.dir/build.make CMakeFiles/OptBlur.dir/experiments/OptBlur.cpp.s
.PHONY : experiments/OptBlur.cpp.s

experiments/Read.o: experiments/Read.cpp.o

.PHONY : experiments/Read.o

# target to build an object file
experiments/Read.cpp.o:
	$(MAKE) -f CMakeFiles/Read.dir/build.make CMakeFiles/Read.dir/experiments/Read.cpp.o
.PHONY : experiments/Read.cpp.o

experiments/Read.i: experiments/Read.cpp.i

.PHONY : experiments/Read.i

# target to preprocess a source file
experiments/Read.cpp.i:
	$(MAKE) -f CMakeFiles/Read.dir/build.make CMakeFiles/Read.dir/experiments/Read.cpp.i
.PHONY : experiments/Read.cpp.i

experiments/Read.s: experiments/Read.cpp.s

.PHONY : experiments/Read.s

# target to generate assembly for a file
experiments/Read.cpp.s:
	$(MAKE) -f CMakeFiles/Read.dir/build.make CMakeFiles/Read.dir/experiments/Read.cpp.s
.PHONY : experiments/Read.cpp.s

src/Benchmark.o: src/Benchmark.cpp.o

.PHONY : src/Benchmark.o

# target to build an object file
src/Benchmark.cpp.o:
	$(MAKE) -f CMakeFiles/Benchmark.dir/build.make CMakeFiles/Benchmark.dir/src/Benchmark.cpp.o
.PHONY : src/Benchmark.cpp.o

src/Benchmark.i: src/Benchmark.cpp.i

.PHONY : src/Benchmark.i

# target to preprocess a source file
src/Benchmark.cpp.i:
	$(MAKE) -f CMakeFiles/Benchmark.dir/build.make CMakeFiles/Benchmark.dir/src/Benchmark.cpp.i
.PHONY : src/Benchmark.cpp.i

src/Benchmark.s: src/Benchmark.cpp.s

.PHONY : src/Benchmark.s

# target to generate assembly for a file
src/Benchmark.cpp.s:
	$(MAKE) -f CMakeFiles/Benchmark.dir/build.make CMakeFiles/Benchmark.dir/src/Benchmark.cpp.s
.PHONY : src/Benchmark.cpp.s

src/Main.o: src/Main.cpp.o

.PHONY : src/Main.o

# target to build an object file
src/Main.cpp.o:
	$(MAKE) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/src/Main.cpp.o
.PHONY : src/Main.cpp.o

src/Main.i: src/Main.cpp.i

.PHONY : src/Main.i

# target to preprocess a source file
src/Main.cpp.i:
	$(MAKE) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/src/Main.cpp.i
.PHONY : src/Main.cpp.i

src/Main.s: src/Main.cpp.s

.PHONY : src/Main.s

# target to generate assembly for a file
src/Main.cpp.s:
	$(MAKE) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/src/Main.cpp.s
.PHONY : src/Main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... Blur"
	@echo "... Main"
	@echo "... Grayscale"
	@echo "... Benchmark"
	@echo "... Check"
	@echo "... OptBlur"
	@echo "... Read"
	@echo "... experiments/Blur.o"
	@echo "... experiments/Blur.i"
	@echo "... experiments/Blur.s"
	@echo "... experiments/Check.o"
	@echo "... experiments/Check.i"
	@echo "... experiments/Check.s"
	@echo "... experiments/Grayscale.o"
	@echo "... experiments/Grayscale.i"
	@echo "... experiments/Grayscale.s"
	@echo "... experiments/OptBlur.o"
	@echo "... experiments/OptBlur.i"
	@echo "... experiments/OptBlur.s"
	@echo "... experiments/Read.o"
	@echo "... experiments/Read.i"
	@echo "... experiments/Read.s"
	@echo "... src/Benchmark.o"
	@echo "... src/Benchmark.i"
	@echo "... src/Benchmark.s"
	@echo "... src/Main.o"
	@echo "... src/Main.i"
	@echo "... src/Main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

