Name: ${PROJECT_NAME}
Description: ${PROJECT_DESCRIPTION}
URL: ${PROJECT_URL}
Version: ${PKG_CONFIG_VERSION}
Requires: ${PKG_CONFIG_REQUIRES}
Conflicts: 
Libs: ${LIBDIR_KW}${INSTALL_LIB_PATH} ${PKG_CONFIG_LIBDIR} ${LIBINCL_KW}vision${LIB_EXT} ${ImageMagick_LIBRARIES}
Cflags: -I${INSTALL_HEADERS_PATH} -I${EIGEN3_INCLUDE_DIR} -I${ImageMagick_INCLUDE_DIRS}

