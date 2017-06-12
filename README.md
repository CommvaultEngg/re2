# Introduction

This is a modified version of the source code present in Google RE2. Modifications were made to get it working on a Winx64 machine using Visual Studio 2013.

## Steps followed to get a working DLL

- Download source for Google RE2
- Install CMake
- Use CMake to build re2 source for VS 2013 on Win64. (RE2 comes with its own CMakeLists file)
- Open the generated project in VS 2013
- Change output architecture to win64.
- Try building the re2 project(among the list of projects. (We faced several errors while building it. So we fixed each one till it was built successfully, resulting in the current status of the source files.)

## Using the RE2 DLL

The generated RE2 DLL is located in the compile/Release. Copying this DLL over to any Win64 machine should give access to all of its exposed functions. The DLL has not been tested with Win32 architectures.