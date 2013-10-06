afp-game
========

Game made for TIE-11300 Game programming course

Requirements for compiling this project
* CMake
* SFML 2.1

About CMake
========

If you make any new code files that need to be included in the build process,
you need to add them in to the CMakeLists.txt file to the add executable line.

If we need any subdirectories etc. we'll have a closer look about how to construct
the CMake file

Coding conventions
========

Mark private members with an m prefix (eg. mPlayer).

Use doxygen style commenting. Example:

/// Brief description
///
/// More in-depth description

Doxygen also has all kinds of special identifiers (\return, \class etc.). 
You can read more about Doxygen at http://www.lmgtfy.com?doxygen

ADD YOUR COMPILERS PROJECT FILES TO THE GITIGNORE FILES! DO NOT COMMIT 
COMPILER SPECIFIC FILES TO THE PROJECT! The project has a CMake file
that can be used to generate project files for all kinds of compilers,
use it!
