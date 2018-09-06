##############################################
#
#	By Dorian'B (Dorian Bachelot).
#
##############################################


cmake_minimum_required(VERSION 3.0)

############################################################################
# project name
project (TigiNet)													            																								# project name
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




file(GLOB_RECURSE SCRIPT_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/script/" LIST_DIRECTORIES false 
	"script/*"
)

foreach(SCRIPT ${SCRIPT_LIST})
	message("${SCRIPT}")
    string(REGEX MATCH "([^/]+)$" FILENAME ${SCRIPT})
    string(REGEX REPLACE "\\.| |-" "_" FILENAME ${FILENAME})
	file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/inc/Script/${SCRIPT} "")
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/script/${SCRIPT} SCRIPT_DATA HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," SCRIPT_DATA ${SCRIPT_DATA})
    file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/inc/Script/${SCRIPT} "const unsigned char ${FILENAME}[] = {${SCRIPT_DATA}};\nconst unsigned ${FILENAME}_size = sizeof(${FILENAME});\n")
endforeach()