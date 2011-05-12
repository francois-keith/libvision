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

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )


# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
	set(var INSTALL_${p}_PATH)
	if(NOT IS_ABSOLUTE "${${var}}")
		set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
	endif()
endforeach()



### Search for Lib/Headers

find_package( Eigen3 2.9)
find_package( ImageMagick COMPONENTS Magick++ ) 



### Configure a header file to pass some of the CMake settings
### to the source code


configure_file (
	"${PROJECT_SOURCE_DIR}/vision.h.in"
	"${PROJECT_SOURCE_DIR}/include/vision/vision.h"
)


### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include"
		     "${CMAKE_CURRENT_SOURCE_DIR}/src"
	             "${CMAKE_CURRENT_BINARY_DIR}"
		     "${EIGEN3_INCLUDE_DIR}" )

if ( ImageMagick_Magick++_FOUND )		 
	include_directories ( "${ImageMagick_Magick++_INCLUDE_DIR}" )
endif ( ImageMagick_Magick++_FOUND )		 


### File Lists

file( GLOB src "src/*.cpp" "src/fast/*.cpp" )
file( GLOB hdr "src/*.h*")

file( GLOB hdr_global  "include/vision/*.h*")
file( GLOB hdr_image   "include/vision/image/*.h*")
file( GLOB hdr_camera  "include/vision/camera/*.h*") 
file( GLOB hdr_corners "include/vision/corners/*.h*") 
file( GLOB hdr_io      "include/vision/io/*.h*") 
file( GLOB hdr_color   "include/vision/color/*.h*") 


### Targets

add_library( "vision" SHARED ${src} ${hdr} )


if ( ImageMagick_Magick++_FOUND )		 
	target_link_libraries ( "vision" "${ImageMagick_Magick++_LIBRARIES}" ) 
endif ( ImageMagick_Magick++_FOUND )		 

### INSTAll

install( TARGETS "vision"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
	    ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

install( FILES ${hdr_global}
	    DESTINATION ${INSTALL_HEADERS_PATH}/vision/${name}
	    COMPONENT main )
install( FILES ${hdr_image}
	    DESTINATION ${INSTALL_HEADERS_PATH}/vision/image/${name}
	    COMPONENT main )
install( FILES ${hdr_camera}
	    DESTINATION ${INSTALL_HEADERS_PATH}/vision/camera/${name}
	    COMPONENT main )
install( FILES ${hdr_corners}
	    DESTINATION ${INSTALL_HEADERS_PATH}/vision/corners/${name}
	    COMPONENT main )
install( FILES ${hdr_io}
	    DESTINATION ${INSTALL_HEADERS_PATH}/vision/io/${name}
	    COMPONENT main )
install( FILES ${hdr_color}
	    DESTINATION ${INSTALL_HEADERS_PATH}/vision/color/${name}
	    COMPONENT main )


### Configure file

configure_file(visionConfig.cmake.in "${PROJECT_BINARY_DIR}/visionConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/visionConfig.cmake" 
	  DESTINATION "${INSTALL_LIB_PATH}/vision" COMPONENT dev )  
        

