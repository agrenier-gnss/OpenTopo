# Open Soft

	The Open Soft project is a subdivision of Open Topo.
The goal is to implement a plugin for [LibreCAD](http://www.librecad.org) software, which aims to be an
open source alternative to software like Covadis or Topstation.



## Build

We currently work with a CMake for developpement purpose.
	* Run ```./configure [-g]``` at root, with option -g if you want to debbug
	* Then use the Makefile which is at root of the project.
	* You can use the following rules :
		* make all
		* make clean
		* make distclean

Requirement:
	* [LibreCAD](http://www.librecad.org) software
	* [Qt](http://www.qt.io/download-open-source/) 5.2.1+ (MinGW on Windows)
	* [Boost](http://www.boost.org/)


## Code
We're working in C++ 11 to be compatible with LibreCAD and use Qt.



## Contributors
	If you want to help with this project, please contact Antoine GRENIER or Mailys HAU.
(see AUTHORS for mor info)
