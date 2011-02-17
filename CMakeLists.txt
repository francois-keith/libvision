# CMake file for Vision library
#
#    From the off-tree build directory, invoke:
#	 cmake <PATH_TO_lib_vision>
#
#
#   - Feb 2010: Initial version <druon@lirmm.fr>
#
# ----------------------------------------------------------------------------

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )

cmake_minimum_required (VERSION 2.6)

project (Vision)
set (Vision_VERSION_MAJOR 0)
set (Vision_VERSION_MINOR 1)




# Configure a header file to pass some of the CMake settings
# to the source code

configure_file (
	"${PROJECT_SOURCE_DIR}/Config.h.in"
	"${PROJECT_SOURCE_DIR}/src/Config.h"
)


## Search for Lib/Headers

set ( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ) 

find_package(Eigen3 3.1.2)


## Set include directories 
        
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include"
		    "${CMAKE_CURRENT_SOURCE_DIR}/src"
	            "${CMAKE_CURRENT_BINARY_DIR}"
		    "${EIGEN_PATH}" )
	
file(GLOB lib_srcs "src/*.cpp")
file(GLOB lib_int_hdrs "src/*.h*")
#source_group("Src" FILES ${lib_srcs} ${lib_int_hdrs})

file(GLOB lib_hdrs "include/*.h*")
#source_group("Include" FILES ${lib_hdrs})

add_library( "vision" ${lib_srcs} ${lib_hdrs} ${lib_int_hdrs})

install(TARGETS "vision"
	    RUNTIME DESTINATION bin COMPONENT main
	    LIBRARY DESTINATION lib COMPONENT main
	    ARCHIVE DESTINATION lib COMPONENT main)

install(FILES ${lib_hdrs}
	    DESTINATION include/vision/${name}
	    COMPONENT main)

