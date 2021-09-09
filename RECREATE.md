
Steps Followed:

#### Download CMake
https://cmake.org/download/
Windows x64 Installer: cmake-3.21.2-windows-x86_64.msi
#### Download GLFW 3.3.4
https://www.glfw.org/download.html
Source package
#### Download Glad
https://glad.dav1d.de/
Language: C/C++
Specification: OpenGL
API:
    gl: Version 3.3
    Profile: Core
#### Using CMake on extracted folder from glfw3.3
Output folder: build
Configure to use Visual Studio 16 2019
Configure again and then generate

#### Open the Visual Studio Solution generated in above step and Build the Solution
#### Import the build/src/Debug/glfw3.lib to lib/
#### Import the original/include/GLFW to include/
#### Import glad/include/ glad, KHR folders to include/
#### Import src/glad.c to your src folder
#### Select x64 next to Debug Option
#### Project Setting -> All Platforms
      VC++ Directories -> Add Lib Folder for libraries
                       -> Add Include folder for Includes
      Linker -> Input -> Additional Dependencies
                        Add glfw3.lib opengl32.lib
#### Drag and Drop glad.c from File Explorer to Source Files Directory in Visual Studio
#### Add a dummy Main.cpp file to check the compilation is working
```
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	return 0;
}
```
#### 

Youtube Tutorial
[Link] (https://www.youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-)

[Glad] (https://glad.dav1d.de/)
[GLFW] (https://www.glfw.org/download.html)
