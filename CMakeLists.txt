##############################################
#
#	By Dorian'B (Dorian Bachelot).
#
##############################################


cmake_minimum_required(VERSION 3.0)

############################################################################
# project name
project (TigiNet)																																					# project name
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
		message("x64 config")
	else()													# if x86
		message("x86 config")
endif()