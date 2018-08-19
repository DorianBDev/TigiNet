##############################################
#
#	By Dorian'B (Dorian Bachelot).
#
##############################################

# get all sub directory <=> sub projects
file(GLOB SUB_PROJECTS_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" LIST_DIRECTORIES true 
	"*"
)

foreach(SUB_PROJECTS ${SUB_PROJECTS_LIST})
	if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUB_PROJECTS})
		add_subdirectory("${SUB_PROJECTS}")
	endif()
endforeach()