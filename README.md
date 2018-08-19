
# TIGINET ([PROJECT WEBSITE](https://dorianbdev.github.io/TigiNet/docs/index.html))
By **Dorian'B**.

| Platform| x64 | x32 |
|--|--|--|
| Windows | [![Build status](https://ci.appveyor.com/api/projects/status/07vjqfu6jo79obtt/branch/master?svg=true)](https://ci.appveyor.com/project/DorianBDev/tiginet/branch/master) | [![Build status](https://ci.appveyor.com/api/projects/status/07vjqfu6jo79obtt/branch/master?svg=true)](https://ci.appveyor.com/project/DorianBDev/tiginet/branch/master) |
| Linux| [![Build Status](https://travis-ci.org/DorianBDev/TigiNet.svg?branch=master)](https://travis-ci.org/DorianBDev/TigiNet) | [![Build Status](https://travis-ci.org/DorianBDev/TigiNet.svg?branch=master)](https://travis-ci.org/DorianBDev/TigiNet) |



## About
TigiNet is a **neural network library** who provide for the moment only support for multilayer perceptron.


### Features :
 - Support for **Multilayer Perceptron**.
 - **Multithreading** support.
 
### Todo/Future :
 - [ ] Support more neural network type.
 - [x] Multiplatform support.
 - [ ] **GPU** support *(with OpenCL)*.
 
[See the trello for more](https://trello.com/b/GPXij9uG/tiginet)
 

## OpenCL support

To work with OpenCL *(for the GPU usage support)* if the support for your platform isn't yet implemented you need to :

 - Download latest header of OpenCL [here](https://github.com/KhronosGroup/OpenCL-Headers).
 - Add the headers in the *"include/CL/"* directory.
 - Build the library *"OpenCL ICD Loader library"*, [available here](https://github.com/KhronosGroup/OpenCL-ICD-Loader).
 - Follow the instructions of the link to build (don't forget to place headers (see above) in the *"inc/CL/"*).
 - Add the binaries in the *"lib/CL/"* folder : *OpenCL/libOpenCL .dll/.lib/.o*.

For windows the .bat in source of *OpenCL ICD Loader library* **may cause problems**, for me I juste needed to replace the first line with :

 - For x64 :

    call "(ABSOLUTE PATH FOR VISUAL STUDIO)\VC\Auxiliary\Build\vcvars64.bat"

 - For x86 :

    call "(ABSOLUTE PATH FOR VISUAL STUDIO)\VC\Auxiliary\Build\vcvars32.bat"
	
	
## Other

 - One commit per module (e.g : [Core] Changement in core.)
 
 
## Versioning

### Fomat :
 - vMAJOR.MINOR.PATCH-{release/nightly/hotfix/rc}
 - Use this version as git tag with 'release' for master branch, 'nightly' for develop branch, 'hotfix' for hotfix branch and 'rc' for release branch (release candidate).
 - For a new version change this file in a commit and only this file and tag it with this version naming.
 - All changements and new features for a new version need to appear in the CHANGELOG file.
 - Need to push the new version commit and after that create the tag and push it.

### All branches :
 - master branch : only for release.
 - develop branch : nightly branch, to prepare a new version, the working branch.
 - hotfix branch : to fix a previous release without new features.
 - release branch : pre release/release candidate branch.
 

### Other :
 - See : git tag commands, git commands for changing branch.
 - Use git describe to know the version of a commit (with the form : vMAJOR.MINOR.PATCH-{release/nightly/hotfix/rc}-{Number of commit for this verison}-{actual commit hash} )
 

## License

Under GNU General Public License v3.0. See LICENSE file for more.

	TIGINET
    Copyright (C) 2018  BACHELOT Dorian
	
	For contact see CONTACT.md file.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
	
	See LICENSE file for more.

	
## Contact

For contact see CONTACT.md file.


## Wiki

### Add dependencies
To add a dependency you simply need : 
(*If the dependency is a module/subproject/subdir you can jump to 3. directly.*)

 1. Add all dependency headers in *thirdparty/inc/*
 2. Add the dependency **shared or static** lib in the *lib/[x86 AND x64]/*
 3. Go to your targeted module/subproject/subdir folder in *src/[YOUR MODULE]/* and open the CMakeLists.txt
 4. Add the name of the dependency to this line : *set(TARGET_DEPENDENCIES "name_of_the_dependency_1;name_of_the_dependency_2;[THE NAME HERE]" CACHE STRING "List of others dependencies name." FORCE)*
 5. Rebuild the project with CMake

### Build
To build with CMake you need :

 1. Go to *build/[x86 OR x64]/*
 2. Call cmake ../../ -G [YOUR TARGETED GENERATORS/IDE X86 OR X64]

e.g. : Visual studio :
*cmake ../../ -G "Visual Studio 15 2017 ARM"* (for x86)
*cmake ../../ -G "Visual Studio 15 2017 Win64"* (for x64)

**call : *cmake --help for generators list.***

### Project Tree

    build/
    	|	- x86/
    	|	- x64/
		|  - .../
    inc/
    	|	- Module_A/
	    |	- Module_B/
	    |   - sharedHeaders.h
    src/
	    |	- Module_A/
	    |	- Module_B/
    thirdparty/
    	|	- inc/
    	|	- lib/
    	|		|	- x86/
    	|		|	- x64/
	docs/
	examples/
	res/

 - *build/* : where generate project with cmake.
 - *inc/* : your project headers.
 - *src/* : your project sources.
 - *thirdparty/* : all dependencies.
 - *docs/* : where are the documentations and the website.
 - *examples/* : where are some examples and all file form samples.
 - *res/* : all ressources for the library.

### Project organization
This sample project is organized in 'Module', each can be build separately. Each module need to have :

 1. His folder in *inc/*
 2. His folder in *src/*
 3. His *CMakeLists.txt* in *src/[YOUR MODULE NAME]/*

Each module can be configured in his *CMakeLists.txt*.

You can have *Shared Headers* in *inc/*.


### Add module/subproject/subdir
To add a module you need :

 1. Add folder in (name of the module) *inc/*
 2. Add folder in (name of the module) *src/*
 3. Add a *CMakeLists.txt* in *src/[YOUR MODULE NAME]/* (you can copy one *CMakeLists.txt* from another module and just change dependency list and target type (executable or library))

To configure you module you need to set the target type :

 Change this two lines : 
 
- *set(TARGET_TYPE "[YOUR TYPE]" CACHE STRING "Type of the target : EXE for executable and LIB:<type> for a library (<type> can be : SHARED or STATIC or MODULE)." FORCE)*
- set(TARGET_DEPENDENCIES "[YOUR DEPENDENCIES LIST]" CACHE STRING "List of others dependencies name." FORCE)
 
 [YOUR TYPE] can be :
 

 - *EXE* for create an executable.
 - *LIB:SHARED* for create a shared library.
 - *LIB:STATIC* for create a static library.

[YOUR DEPENDENCIES LIST] need to be like this : name_of_the_dependency_1;name_of_the_dependency_2... See the **Add dependencies** point for more.
**Write *NONE* if you have no dependencies**

### Compile for 32 or 64 bits

To compile for *32* or *64 bits* you need :

On windows :

 - Build your project for *Visual Studio [VERSION] ARM* for *x86*
 - Build your project for *Visual Studio [VERSION] WIN64* for *x64*

On linux :

 - Build your project with CMake normaly for *x64*
 - Build your project with CMake with the options :
 *-DCMAKE_CXX_FLAGS=-m32 -DCMAKE_C_FLAGS=-m32* for *x86*

(for linux care you have already the package to compile c++ in 32bits, otherwise you need this two packages : *sudo apt-get install libc6-dev-i386* and *sudo apt-get install g++-7-multilib*
 
You already got two folder in the *build/* directory for *x64* and *x86*.

### Other

 - **If you want to add a file with Visual Studio, add it manually and not in VS !**


## TIGINET

![TIGINET Logo](res/logo/logo_sp_text.png)