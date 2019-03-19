##############################################################################
####																			
####   TIGINET																	
####   Copyright (C) 2018-2019  BACHELOT Dorian									
####																			
####   For contact see CONTACT.md file.											
####																			
####   This program is free software: you can redistribute it and/or modify		
####   it under the terms of the GNU General Public License as published by		
####   the Free Software Foundation, either version 3 of the License, or		
####   (at your option) any later version.										
####																			
####   This program is distributed in the hope that it will be useful,			
####   but WITHOUT ANY WARRANTY; without even the implied warranty of			
####   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			
####   GNU General Public License for more details.								
####																			
####   You should have received a copy of the GNU General Public License		
####   along with this program.  If not, see <https://www.gnu.org/licenses/>.	
####																			
####	See LICENSE file for more.												
####																			
##############################################################################


cmake_minimum_required(VERSION 3.0)

############################################################################
############################################################################
###########################   CONFIG   #####################################
############################################################################
############################################################################

# project name
project (TigiNet)													            																								# project name

############################################################################
############################################################################
############################################################################
############################################################################
############################################################################


# cxx flag
set(CMAKE_BUILD_TYPE Debug)																																		# choose language en flags
set(CMAKE_CXX_STANDARD 14)
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(MSVC)

# property for folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)

if (CMAKE_SIZEOF_VOID_P MATCHES 8) # if x64
		message("-- x64 configuration")
	else()													# if x86
		message("-- x86 configuration")
endif()