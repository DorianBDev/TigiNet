# TIGINET
**Projet website** : https://dorianbdev.github.io/TigiNet/docs/index.html

By **Dorian'B**.

| Platform| Status |
|--|--|
| Windows | [![Build status](https://ci.appveyor.com/api/projects/status/07vjqfu6jo79obtt/branch/master?svg=true)](https://ci.appveyor.com/project/DorianBDev/tiginet/branch/master) |
| Linux | [![Build Status](https://travis-ci.org/DorianBDev/TigiNet.svg?branch=master)](https://travis-ci.org/DorianBDev/TigiNet) |



## About
TigiNet is a **neural network library** who provide for the moment only support for multilayer perceptron.


### Features :
 - Support for **Multilayer Perceptron**.
 - **Multithreading** support.
 
### Wiki :
Visit the wiki here : https://github.com/DorianBDev/TigiNet/wiki
 
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


## TIGINET

![TIGINET Logo](res/logo/logo_sp_text.png)