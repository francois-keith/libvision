### CMake file example to use vision library
###
###   - Feb 2010: Initial version <druon@lirmm.fr>
###
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project ( example )
set (vision_VERSION_MAJOR 0)
set (vision_VERSION_MINOR 1)

find_package( vision )

include_directories ( ${VISION_INCLUDE_DIRS} )
link_directories    ( ${VISION_LIBRARY_DIR} )

file( GLOB src "*.cpp")
file( GLOB hdr "*.h*")

### Targets

add_executable( "LoadSave_RGB" ${src}  ${hdr} )

target_link_libraries ( "LoadSave_RGB" ${VISION_LIBRARIES} ) 

