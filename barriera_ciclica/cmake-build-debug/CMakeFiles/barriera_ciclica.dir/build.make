# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\barriera_ciclica.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\barriera_ciclica.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\barriera_ciclica.dir\flags.make

CMakeFiles\barriera_ciclica.dir\main.cpp.obj: CMakeFiles\barriera_ciclica.dir\flags.make
CMakeFiles\barriera_ciclica.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/barriera_ciclica.dir/main.cpp.obj"
	"C:\PROGRA~2\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.25.28610\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\barriera_ciclica.dir\main.cpp.obj /FdCMakeFiles\barriera_ciclica.dir\ /FS -c C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\main.cpp
<<

CMakeFiles\barriera_ciclica.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/barriera_ciclica.dir/main.cpp.i"
	"C:\PROGRA~2\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.25.28610\bin\Hostx86\x86\cl.exe" > CMakeFiles\barriera_ciclica.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\main.cpp
<<

CMakeFiles\barriera_ciclica.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/barriera_ciclica.dir/main.cpp.s"
	"C:\PROGRA~2\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.25.28610\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\barriera_ciclica.dir\main.cpp.s /c C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\main.cpp
<<

# Object files for target barriera_ciclica
barriera_ciclica_OBJECTS = \
"CMakeFiles\barriera_ciclica.dir\main.cpp.obj"

# External object files for target barriera_ciclica
barriera_ciclica_EXTERNAL_OBJECTS =

barriera_ciclica.exe: CMakeFiles\barriera_ciclica.dir\main.cpp.obj
barriera_ciclica.exe: CMakeFiles\barriera_ciclica.dir\build.make
barriera_ciclica.exe: CMakeFiles\barriera_ciclica.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable barriera_ciclica.exe"
	"C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\barriera_ciclica.dir --rc="C:\PROGRA~2\Windows Kits\10\bin\10.0.18362.0\x86\rc.exe" --mt="C:\PROGRA~2\Windows Kits\10\bin\10.0.18362.0\x86\mt.exe" --manifests  -- "C:\PROGRA~2\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.25.28610\bin\Hostx86\x86\link.exe" /nologo @CMakeFiles\barriera_ciclica.dir\objects1.rsp @<<
 /out:barriera_ciclica.exe /implib:barriera_ciclica.lib /pdb:C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\cmake-build-debug\barriera_ciclica.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\barriera_ciclica.dir\build: barriera_ciclica.exe

.PHONY : CMakeFiles\barriera_ciclica.dir\build

CMakeFiles\barriera_ciclica.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\barriera_ciclica.dir\cmake_clean.cmake
.PHONY : CMakeFiles\barriera_ciclica.dir\clean

CMakeFiles\barriera_ciclica.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\cmake-build-debug C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\cmake-build-debug C:\Users\isnob\CLionProjects\cpp_lab\barriera_ciclica\cmake-build-debug\CMakeFiles\barriera_ciclica.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\barriera_ciclica.dir\depend

