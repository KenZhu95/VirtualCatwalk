# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /mnt/c/CG/Projects/Skin/skinning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/CG/Projects/Skin/skinning/build

# Include any dependencies generated for this target.
include src/CMakeFiles/skinning.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/skinning.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/skinning.dir/flags.make

src/CMakeFiles/skinning.dir/bone_geometry.cc.o: src/CMakeFiles/skinning.dir/flags.make
src/CMakeFiles/skinning.dir/bone_geometry.cc.o: ../src/bone_geometry.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CG/Projects/Skin/skinning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/skinning.dir/bone_geometry.cc.o"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/skinning.dir/bone_geometry.cc.o -c /mnt/c/CG/Projects/Skin/skinning/src/bone_geometry.cc

src/CMakeFiles/skinning.dir/bone_geometry.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/skinning.dir/bone_geometry.cc.i"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CG/Projects/Skin/skinning/src/bone_geometry.cc > CMakeFiles/skinning.dir/bone_geometry.cc.i

src/CMakeFiles/skinning.dir/bone_geometry.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/skinning.dir/bone_geometry.cc.s"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CG/Projects/Skin/skinning/src/bone_geometry.cc -o CMakeFiles/skinning.dir/bone_geometry.cc.s

src/CMakeFiles/skinning.dir/bone_geometry.cc.o.requires:

.PHONY : src/CMakeFiles/skinning.dir/bone_geometry.cc.o.requires

src/CMakeFiles/skinning.dir/bone_geometry.cc.o.provides: src/CMakeFiles/skinning.dir/bone_geometry.cc.o.requires
	$(MAKE) -f src/CMakeFiles/skinning.dir/build.make src/CMakeFiles/skinning.dir/bone_geometry.cc.o.provides.build
.PHONY : src/CMakeFiles/skinning.dir/bone_geometry.cc.o.provides

src/CMakeFiles/skinning.dir/bone_geometry.cc.o.provides.build: src/CMakeFiles/skinning.dir/bone_geometry.cc.o


src/CMakeFiles/skinning.dir/gui.cc.o: src/CMakeFiles/skinning.dir/flags.make
src/CMakeFiles/skinning.dir/gui.cc.o: ../src/gui.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CG/Projects/Skin/skinning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/skinning.dir/gui.cc.o"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/skinning.dir/gui.cc.o -c /mnt/c/CG/Projects/Skin/skinning/src/gui.cc

src/CMakeFiles/skinning.dir/gui.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/skinning.dir/gui.cc.i"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CG/Projects/Skin/skinning/src/gui.cc > CMakeFiles/skinning.dir/gui.cc.i

src/CMakeFiles/skinning.dir/gui.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/skinning.dir/gui.cc.s"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CG/Projects/Skin/skinning/src/gui.cc -o CMakeFiles/skinning.dir/gui.cc.s

src/CMakeFiles/skinning.dir/gui.cc.o.requires:

.PHONY : src/CMakeFiles/skinning.dir/gui.cc.o.requires

src/CMakeFiles/skinning.dir/gui.cc.o.provides: src/CMakeFiles/skinning.dir/gui.cc.o.requires
	$(MAKE) -f src/CMakeFiles/skinning.dir/build.make src/CMakeFiles/skinning.dir/gui.cc.o.provides.build
.PHONY : src/CMakeFiles/skinning.dir/gui.cc.o.provides

src/CMakeFiles/skinning.dir/gui.cc.o.provides.build: src/CMakeFiles/skinning.dir/gui.cc.o


src/CMakeFiles/skinning.dir/main.cc.o: src/CMakeFiles/skinning.dir/flags.make
src/CMakeFiles/skinning.dir/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CG/Projects/Skin/skinning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/skinning.dir/main.cc.o"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/skinning.dir/main.cc.o -c /mnt/c/CG/Projects/Skin/skinning/src/main.cc

src/CMakeFiles/skinning.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/skinning.dir/main.cc.i"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CG/Projects/Skin/skinning/src/main.cc > CMakeFiles/skinning.dir/main.cc.i

src/CMakeFiles/skinning.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/skinning.dir/main.cc.s"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CG/Projects/Skin/skinning/src/main.cc -o CMakeFiles/skinning.dir/main.cc.s

src/CMakeFiles/skinning.dir/main.cc.o.requires:

.PHONY : src/CMakeFiles/skinning.dir/main.cc.o.requires

src/CMakeFiles/skinning.dir/main.cc.o.provides: src/CMakeFiles/skinning.dir/main.cc.o.requires
	$(MAKE) -f src/CMakeFiles/skinning.dir/build.make src/CMakeFiles/skinning.dir/main.cc.o.provides.build
.PHONY : src/CMakeFiles/skinning.dir/main.cc.o.provides

src/CMakeFiles/skinning.dir/main.cc.o.provides.build: src/CMakeFiles/skinning.dir/main.cc.o


src/CMakeFiles/skinning.dir/procedure_geometry.cc.o: src/CMakeFiles/skinning.dir/flags.make
src/CMakeFiles/skinning.dir/procedure_geometry.cc.o: ../src/procedure_geometry.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CG/Projects/Skin/skinning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/skinning.dir/procedure_geometry.cc.o"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/skinning.dir/procedure_geometry.cc.o -c /mnt/c/CG/Projects/Skin/skinning/src/procedure_geometry.cc

src/CMakeFiles/skinning.dir/procedure_geometry.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/skinning.dir/procedure_geometry.cc.i"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CG/Projects/Skin/skinning/src/procedure_geometry.cc > CMakeFiles/skinning.dir/procedure_geometry.cc.i

src/CMakeFiles/skinning.dir/procedure_geometry.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/skinning.dir/procedure_geometry.cc.s"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CG/Projects/Skin/skinning/src/procedure_geometry.cc -o CMakeFiles/skinning.dir/procedure_geometry.cc.s

src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.requires:

.PHONY : src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.requires

src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.provides: src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.requires
	$(MAKE) -f src/CMakeFiles/skinning.dir/build.make src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.provides.build
.PHONY : src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.provides

src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.provides.build: src/CMakeFiles/skinning.dir/procedure_geometry.cc.o


src/CMakeFiles/skinning.dir/render_pass.cc.o: src/CMakeFiles/skinning.dir/flags.make
src/CMakeFiles/skinning.dir/render_pass.cc.o: ../src/render_pass.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CG/Projects/Skin/skinning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/skinning.dir/render_pass.cc.o"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/skinning.dir/render_pass.cc.o -c /mnt/c/CG/Projects/Skin/skinning/src/render_pass.cc

src/CMakeFiles/skinning.dir/render_pass.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/skinning.dir/render_pass.cc.i"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CG/Projects/Skin/skinning/src/render_pass.cc > CMakeFiles/skinning.dir/render_pass.cc.i

src/CMakeFiles/skinning.dir/render_pass.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/skinning.dir/render_pass.cc.s"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CG/Projects/Skin/skinning/src/render_pass.cc -o CMakeFiles/skinning.dir/render_pass.cc.s

src/CMakeFiles/skinning.dir/render_pass.cc.o.requires:

.PHONY : src/CMakeFiles/skinning.dir/render_pass.cc.o.requires

src/CMakeFiles/skinning.dir/render_pass.cc.o.provides: src/CMakeFiles/skinning.dir/render_pass.cc.o.requires
	$(MAKE) -f src/CMakeFiles/skinning.dir/build.make src/CMakeFiles/skinning.dir/render_pass.cc.o.provides.build
.PHONY : src/CMakeFiles/skinning.dir/render_pass.cc.o.provides

src/CMakeFiles/skinning.dir/render_pass.cc.o.provides.build: src/CMakeFiles/skinning.dir/render_pass.cc.o


# Object files for target skinning
skinning_OBJECTS = \
"CMakeFiles/skinning.dir/bone_geometry.cc.o" \
"CMakeFiles/skinning.dir/gui.cc.o" \
"CMakeFiles/skinning.dir/main.cc.o" \
"CMakeFiles/skinning.dir/procedure_geometry.cc.o" \
"CMakeFiles/skinning.dir/render_pass.cc.o"

# External object files for target skinning
skinning_EXTERNAL_OBJECTS =

bin/skinning: src/CMakeFiles/skinning.dir/bone_geometry.cc.o
bin/skinning: src/CMakeFiles/skinning.dir/gui.cc.o
bin/skinning: src/CMakeFiles/skinning.dir/main.cc.o
bin/skinning: src/CMakeFiles/skinning.dir/procedure_geometry.cc.o
bin/skinning: src/CMakeFiles/skinning.dir/render_pass.cc.o
bin/skinning: src/CMakeFiles/skinning.dir/build.make
bin/skinning: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/skinning: /usr/lib/x86_64-linux-gnu/libGL.so
bin/skinning: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/skinning: libutgraphicsutil.a
bin/skinning: /home/kenzhu0820/anaconda3/lib/libjpeg.so
bin/skinning: libpmdreader.a
bin/skinning: /home/kenzhu0820/anaconda3/lib/libjpeg.so
bin/skinning: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/skinning: src/CMakeFiles/skinning.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/CG/Projects/Skin/skinning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../bin/skinning"
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/skinning.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/skinning.dir/build: bin/skinning

.PHONY : src/CMakeFiles/skinning.dir/build

src/CMakeFiles/skinning.dir/requires: src/CMakeFiles/skinning.dir/bone_geometry.cc.o.requires
src/CMakeFiles/skinning.dir/requires: src/CMakeFiles/skinning.dir/gui.cc.o.requires
src/CMakeFiles/skinning.dir/requires: src/CMakeFiles/skinning.dir/main.cc.o.requires
src/CMakeFiles/skinning.dir/requires: src/CMakeFiles/skinning.dir/procedure_geometry.cc.o.requires
src/CMakeFiles/skinning.dir/requires: src/CMakeFiles/skinning.dir/render_pass.cc.o.requires

.PHONY : src/CMakeFiles/skinning.dir/requires

src/CMakeFiles/skinning.dir/clean:
	cd /mnt/c/CG/Projects/Skin/skinning/build/src && $(CMAKE_COMMAND) -P CMakeFiles/skinning.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/skinning.dir/clean

src/CMakeFiles/skinning.dir/depend:
	cd /mnt/c/CG/Projects/Skin/skinning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/CG/Projects/Skin/skinning /mnt/c/CG/Projects/Skin/skinning/src /mnt/c/CG/Projects/Skin/skinning/build /mnt/c/CG/Projects/Skin/skinning/build/src /mnt/c/CG/Projects/Skin/skinning/build/src/CMakeFiles/skinning.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/skinning.dir/depend

