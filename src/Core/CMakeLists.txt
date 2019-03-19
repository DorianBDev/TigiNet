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


############################################################################
############################################################################
###########################   CONFIG   #####################################
############################################################################
############################################################################


################################################
# Target type
# DOC : Type of the target : EXE for executable and LIB:<type> for a library (<type> can be : SHARED or STATIC or MODULE)
set(TARGET_TYPE "LIB:SHARED" CACHE STRING "Type of the target : EXE for executable and LIB:<type> for a library (<type> can be : SHARED or STATIC or MODULE)." FORCE)


################################################
# Dependencies list
# DOC : List of others dependencies name (CARE : YOU NEED TO HAVE A ';' BETWEEN EACH DEPENDENCY)
set(TARGET_DEPENDENCIES "NONE" CACHE STRING "List of others dependencies name." FORCE)


################################################
# Optional
# DOC : Add a macro definition for this target when his type is a shared library.
set(TARGET_MACRO_DEF "TN_CORE_EXPORT" CACHE STRING "Add a macro definition for this target when his type is a shared library." FORCE)


################################################
# Target prefix
# DOC : the prefix in the output name.
set(TARGET_PREFIX "TN" CACHE STRING "the prefix in the output name." FORCE)


############################################################################
############################################################################
############################################################################
############################################################################
############################################################################


# Main project folder name
############################################################################
# automatic target name																																					# Target/module name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
set(PROJECT_FOLDER_NAME ${PROJECT_ID})
# or custom target name
#set(PROJECT_FOLDER_NAME "projectA")
############################################################################

# src folder of the project (where the CMakeLists.txt is for this project)
file(GLOB_RECURSE  SRC_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" LIST_DIRECTORIES false 
	"*"
)

# headers of the project
file(GLOB_RECURSE  HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" LIST_DIRECTORIES false 
	"../../inc/${PROJECT_FOLDER_NAME}/*"
)

# share headers for all projects
file(GLOB SHARE_HEADERS_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" LIST_DIRECTORIES false 
	"../../inc/*"
)

# include directory
include_directories("../../inc/")

# inlude third party includes directory
include_directories("../../thirdparty/inc")

############################################################################				# Dependencies

macro(LinkAllDirectories _DIR)
	LINK_DIRECTORIES("${_DIR}")
	unset(FULL_LIST)
	list(APPEND FULL_LIST "")

	
	file(GLOB SUB_DIR_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${_DIR}" LIST_DIRECTORIES true 
		"${CMAKE_CURRENT_SOURCE_DIR}/${_DIR}*"
	)

	foreach(SUB_DIR ${SUB_DIR_LIST})
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_DIR}${SUB_DIR})
			list(APPEND FULL_LIST "${_DIR}${SUB_DIR}")
		endif()
	endforeach()

	
	foreach(DIR ${FULL_LIST})
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})
			LinkAllDirectories("${DIR}")
		endif()
	endforeach()
endmacro()

if(NOT "${TARGET_DEPENDENCIES}" MATCHES "NONE")
	if (CMAKE_SIZEOF_VOID_P MATCHES 8) # if x64
		LinkAllDirectories(../../thirdparty/lib/x64/)
	else()													# if x86
		LinkAllDirectories(../../thirdparty/lib/x86/)
	endif()
endif()

############################################################################

############################################################################
# macro to keep folders tree
macro(GroupSources _LIST)
	foreach(SOURCE ${_LIST})
		get_filename_component(GROUP_NAME "${SOURCE}" PATH)
		string(REPLACE "../../inc/${PROJECT_FOLDER_NAME}/" "" GROUP_NAME "${GROUP_NAME}")
		string(REPLACE "../../inc/${PROJECT_FOLDER_NAME}" "" GROUP_NAME "${GROUP_NAME}")
		string(REPLACE "/" "\\" GROUP_NAME "${GROUP_NAME}")
		
		# Group into "Source Files" and "Header Files"
		if("${SOURCE}" MATCHES "CMakeLists.txt")
			set(GROUP "")
		elseif ("${SOURCE}" MATCHES ".*\\.cpp" OR "${SOURCE}" MATCHES ".*\\.c")															# 'Source Files' folder
		   set(GROUP "Source Files\\${GROUP_NAME}")
		elseif("${SOURCE}" MATCHES ".*\\.hpp" OR "${SOURCE}" MATCHES ".*\\.h" OR "${SOURCE}" MATCHES ".*\\.inl")	# 'Header Files' folder
		   set(GROUP "Header Files\\${GROUP_NAME}")
		else()																																										# 'Other Files' folder
			set(GROUP "Other Files\\${GROUP_NAME}")
		endif()
		
		source_group("${GROUP}" FILES "${SOURCE}")
	endforeach()
endmacro()

source_group("Shared Header Files\\" FILES "${SHARE_HEADERS_FILES}")																		# 'Shared Header Files' folder
############################################################################

# group src
GroupSources("${SRC_FILES}")

# group headers
GroupSources("${HEADER_FILES}")

############################################################################				# Exe or lib
# create the project type (exe or lib)
if("${TARGET_TYPE}" MATCHES "EXE")
	add_executable(${PROJECT_FOLDER_NAME} ${SRC_FILES} ${HEADER_FILES} ${SHARE_HEADERS_FILES})
elseif("${TARGET_TYPE}" MATCHES "LIB:SHARED")
	add_library(${PROJECT_FOLDER_NAME} SHARED ${SRC_FILES} ${HEADER_FILES} ${SHARE_HEADERS_FILES})
	add_definitions("-D${TARGET_MACRO_DEF}")
elseif("${TARGET_TYPE}" MATCHES "LIB:STATIC")
	add_library(${PROJECT_FOLDER_NAME} STATIC ${SRC_FILES} ${HEADER_FILES} ${SHARE_HEADERS_FILES})
elseif("${TARGET_TYPE}" MATCHES "LIB:MODULE")
	add_library(${PROJECT_FOLDER_NAME} MODULE ${SRC_FILES} ${HEADER_FILES} ${SHARE_HEADERS_FILES})
else()
	message("[ERROR] - Wrong target type for ${PROJECT_FOLDER_NAME} target...")
endif()
#or
# add_library(${PROJECT_FOLDER_NAME} <SHARED|STATIC|MODULE|UNKNOWN> ${ALL_FILES})
############################################################################

############################################################################				# Dependencies

if(NOT "${TARGET_DEPENDENCIES}" MATCHES "NONE")
	TARGET_LINK_LIBRARIES(${PROJECT_FOLDER_NAME} LINK_PUBLIC "${TARGET_DEPENDENCIES}")
endif()

############################################################################

# installation specifications
install (TARGETS ${PROJECT_FOLDER_NAME} DESTINATION ../../out/bin)

# output specifications
set_target_properties(${PROJECT_FOLDER_NAME}																												# Outputs folders
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "../../out/lib"
    LIBRARY_OUTPUT_DIRECTORY "../../out/lib"
    RUNTIME_OUTPUT_DIRECTORY "../../out/bin"
)

# specifie the linker language
############################################################################
set_target_properties(${PROJECT_FOLDER_NAME} PROPERTIES LINKER_LANGUAGE CXX)														# Linker language
############################################################################

# prefix
set_target_properties(${PROJECT_FOLDER_NAME} PROPERTIES PREFIX "${TARGET_PREFIX}")
