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

# get all sub directory <=> sub projects
file(GLOB SUB_PROJECTS_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" LIST_DIRECTORIES true 
	"*"
)

foreach(SUB_PROJECTS ${SUB_PROJECTS_LIST})
	if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUB_PROJECTS})
		add_subdirectory("${SUB_PROJECTS}")
	endif()
endforeach()