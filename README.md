# win32-cmake-template

This is a starting point project for a very basic 64bit Unicode Windows Win32 C++ application using cmake instead of
Visual Studio Solutions that includes an optional notification icon, a single instance option plus a static lib with
GoogleTest.

This allows for writing and debugging win32 applications with Visual Studio, Visual Studio Code or CLion. I imagine it
should also work with any other IDEs that supports cmake, but I have not tried any others and don't plan on it.

## Building

Edit the BuildOptions.cmake file to your liking and build using your IDE of choice.

If you do not have Visual Studio installed you will need to have the Build Tools for Visual Studio installed
from [here](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022).

Another option is to generate the Visual Studio Solution and projects from the command line.

To do this, from the project directory issue the following commands.

```
mkdir build
cd build
cmake ..
```

When the cmake command completes there should be a solution file and several project files in the build folder that can
be opened with Visual Studio or built from the command line using msbuild.