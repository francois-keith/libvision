### CMake file for vision library
###
###    From the off-tree build directory, invoke:
###     cmake <PATH_TO_lib_vision>
###
###
###   - Feb 2010: Initial version <druon@lirmm.fr>
###
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

set (CMAKE_LEGACY_CYGWIN_WIN32 1)

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
find_package( Boost 1.40.0 COMPONENTS serialization )

IF(NOT WIN32)
    include(FindPkgConfig)
    pkg_check_modules(LIBAVCODEC libavcodec)
    SET(LIBAVCODEC_FOUND_NUMERAL 0)
    IF(LIBAVCODEC_FOUND)
        SET(LIBAVCODEC_FOUND_NUMERAL 1)
        ADD_DEFINITIONS(${LIBAVCODEC_CFLAGS})
        LINK_DIRECTORIES(${LIBAVCODEC_LIBRARY_DIRS})
    ENDIF(LIBAVCODEC_FOUND)

    pkg_check_modules(LIBSWSCALE libswscale)
    IF(LIBSWSCALE_FOUND)
        ADD_DEFINITIONS(${LIBSWSCALE_CFLAGS})
        LINK_DIRECTORIES(${LIBSWSCALE_LIBRARY_DIRS})
    ENDIF(LIBSWSCALE_FOUND)

    pkg_check_modules(LIBX264 x264)
    IF(LIBX264_FOUND)
        ADD_DEFINITIONS(${LIBX264_CFLAGS})
        LINK_DIRECTORIES(${LIBX264_LIBRARY_DIRS})
    ENDIF(LIBX264_FOUND)
ELSE(NOT WIN32)
### Assume we're compiling with libavcodec support and installed in directories reachable by visual studio
SET(LIBAVCODEC_FOUND 1)
SET(LIBAVCODEC_FOUND_NUMERAL 1)
SET(LIBAVCODEC_LIBRARIES "avutil.lib;avcodec.lib;libx264.lib")

SET(LIBSWSCALE_FOUND 1)
SET(LIBSWSCALE_LIBRARIES "swscale.lib")
ENDIF(NOT WIN32)

### Configure a header file to pass some of the CMake settings
### to the source code

IF(ImageMagick_Magick++_FOUND)
SET(ImageMagick_Magick++_FOUND_BOOL 1)
ELSE(ImageMagick_Magick++_FOUND)
SET(ImageMagick_Magick++_FOUND_BOOL 0)
ENDIF(ImageMagick_Magick++_FOUND)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/include/vision/config.h"
)


### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include"
             "${CMAKE_CURRENT_SOURCE_DIR}/src"
                 "${CMAKE_CURRENT_BINARY_DIR}"
                 "${CMAKE_INSTALL_PREFIX}/include"
             "${EIGEN3_INCLUDE_DIR}" 
             "${Boost_INCLUDE_DIRS}")

if ( ImageMagick_Magick++_FOUND )         
    include_directories ( "${ImageMagick_Magick++_INCLUDE_DIR}" )
endif ( ImageMagick_Magick++_FOUND )         

link_directories("${Boost_LIBRARY_DIRS}")


### File Lists

file( GLOB src "src/*.cpp" "src/fast/*.cpp" "src/win32/windows.cpp" "src/io/*.cpp" )
file( GLOB hdr "src/*.h*")

if(NOT WIN32)
file(GLOB mkv_src "src/io/output/*.c")
set(src $src $mkv_src)
endif(NOT WIN32)

file( GLOB hdr_global  "include/vision/*.h*")
file( GLOB hdr_image   "include/vision/image/*.h*")
file( GLOB hdr_camera  "include/vision/camera/*.h*") 
file( GLOB hdr_corners "include/vision/corners/*.h*") 
file( GLOB hdr_io      "include/vision/io/*.h*") 
file( GLOB hdr_color   "include/vision/color/*.h*") 
file( GLOB hdr_win32   "include/vision/win32/*.h")

file( GLOB visionconfig "vision-config/*.cpp" )


### Targets

add_library( "vision" SHARED ${src} ${hdr} )
target_link_libraries( "vision" ${Boost_LIBRARIES} )
IF(LIBAVCODEC_FOUND)
    target_link_libraries( "vision" ${LIBAVCODEC_LIBRARIES} )
ENDIF(LIBAVCODEC_FOUND)
IF(LIBSWSCALE_FOUND)
    target_link_libraries( "vision" ${LIBSWSCALE_LIBRARIES} )
ENDIF(LIBSWSCALE_FOUND)
IF(LIBX264_FOUND)
    target_link_libraries( "vision" ${LIBX264_LIBRARIES} )
ENDIF(LIBX264_FOUND)

IF(WIN32)
add_library( "vision-static" STATIC ${src} ${hdr} )
set_target_properties( "vision-static" PROPERTIES OUTPUT_NAME "vision")
target_link_libraries( "vision-static" ${Boost_LIBRARIES} ${LIBAVCODEC_LIBRARIES} ${LIBSWSCALE_LIBRARIES} )
ENDIF(WIN32)

add_executable( "vision-config" ${visionconfig}  ${hdr} )


if ( ImageMagick_Magick++_FOUND )         
    target_link_libraries ( "vision" "${ImageMagick_Magick++_LIBRARY}" ) 
    IF(WIN32)
        target_link_libraries ( "vision-static" "${ImageMagick_Magick++_LIBRARY}" ) 
    ENDIF(WIN32)
endif ( ImageMagick_Magick++_FOUND )         

### Tests programs

add_subdirectory( "test" )

### INSTAll

install( TARGETS "vision"
        RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
        LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
        ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

install( TARGETS "vision-config"
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
install( FILES ${hdr_win32}
        DESTINATION ${INSTALL_HEADERS_PATH}/vision/win32/${name}
        COMPONENT main )

### Copy examples to share/lib_vision/examples

INSTALL ( DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples" 
          DESTINATION share/doc/${PROJECT_NAME} )

### Configure file

configure_file(visionConfig.cmake.in "${PROJECT_BINARY_DIR}/visionConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/visionConfig.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/vision" COMPONENT dev )  
        

