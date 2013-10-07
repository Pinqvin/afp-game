afp-game
========

Game made for TIE-11300 Game programming course

Requirements for compiling this project:

* CMake
* SFML 2.1

About CMake
========

If you make any new code files that need to be included in the build process,
you need to add them in to the CMakeLists.txt file to the add executable line.

If we need any subdirectories etc. we'll have a closer look about how to construct
the CMake files.

I'd recommend you build in a separate folder than the source folder. On Linux 
this can be accomplished with the following commands:

```
mkdir build
cd build
cmake ..
make
```

This is just to make sure that you don't accidentally push project (Visual Studio or whatever)
related files to the repository.

CMake and Windows
========

Before you configure your build on windows, you should define a SFML_ROOT path. You can define
 the path in CMake-gui by adding a path entry that points to the SFML-2.1 directory.

 To build Visual Studio 2012 project files, choose Visual Studio 11. Press Configure and Generate, then open
 the afpgame.sln file in the build directory you specified to launch Visual Studio and build the project.

To launch the program on Windows you need to copy all the *.dll files from the SFML-2.1/bin folder to the folder
 with the compiled executable. You also need to compile (at least for now) the Media folder from source root.

Coding conventions
========

Mark private members with an m prefix (eg. mPlayer).

Use doxygen style commenting. Example:

```
/// Brief description
///
/// More in-depth description
```

Doxygen also has all kinds of special identifiers (\return, \class etc.). 
You can read more about Doxygen at http://www.lmgtfy.com/?q=doxygen

ADD YOUR COMPILERS PROJECT FILES TO THE GITIGNORE FILES! DO NOT COMMIT 
COMPILER SPECIFIC FILES TO THE PROJECT! The project has a CMake file
that can be used to generate project files for all kinds of compilers,
use it!
