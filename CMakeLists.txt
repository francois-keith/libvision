### CMake file for vision library
###
###    From the off-tree build directory, invoke:
###	 cmake <PATH_TO_lib_vision>
###
###
###   - Feb 2010: Initial version <druon@lirmm.fr>
###
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (vision)
set (vision_VERSION_MAJOR 0)
set (vision_VERSION_MINOR 1)

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH}  "${PROJECT_SOURCE_DIR}/cmake" ) 

### guard against in-source builds

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()


### Configure a header file to pass some of the CMake settings
### to the source code

configure_file (
	"${PROJECT_SOURCE_DIR}/Config.h.in"
	"${PROJECT_SOURCE_DIR}/src/Config.h"
)


### Search for Lib/Headers

find_package( Eigen3 2.9)


### Set include directories 
        
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include"
		    "${CMAKE_CURRENT_SOURCE_DIR}/src"
	            "${CMAKE_CURRENT_BINARY_DIR}"
		    "${EIGEN3_INCLUDE_DIR}" )


### File Lists

file( GLOB lib_srcs "src/*.cpp" "src/fast/*.cpp" )
file( GLOB lib_int_hdrs "src/*.h*")
file( GLOB lib_hdrs "include/vision/*.h*")


### Targets

add_library( "vision" SHARED ${lib_srcs} ${lib_hdrs} ${lib_int_hdrs})

### install

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH lib )
set ( INSTALL_HEADERS_PATH include/vision )

install( TARGETS "vision"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
	    ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

install( FILES ${lib_hdrs}
	    DESTINATION ${INSTALL_HEADERS_PATH}/${name}
	    COMPONENT main )
### test

configure_file(visionConfig.cmake.in "${PROJECT_BINARY_DIR}/visionConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/visionConfig.cmake" 
	  DESTINATION "${INSTALL_LIB_PATH}/vision" COMPONENT dev )  
        

