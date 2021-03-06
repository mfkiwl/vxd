# This is contrib/brld/CMakeLists.txt

project(brld)

doxygen_add_package(contrib/brld "Brown University Libraries: Development Version")

# In contrib/brld there is sometimes an "extra" level in the directory structure
# (.../contrib/brld/{bbasd,bsegd,bmvld}/foo/foo.h)
# Setting BRLD_INCLUDE_DIR in this way allows #include <foo/foo.h> without
# having to know the internal directory structure.
# The root directory should be listed last in case anyone tries to append to this path
set(BRLD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bbasd;${CMAKE_CURRENT_BINARY_DIR}/bbasd;${CMAKE_CURRENT_SOURCE_DIR}/bmvgd;${CMAKE_CURRENT_BINARY_DIR}/bmvgd;${CMAKE_CURRENT_SOURCE_DIR}/bsegd;${CMAKE_CURRENT_BINARY_DIR}/bsegd;${CMAKE_CURRENT_SOURCE_DIR}/brecd;${CMAKE_CURRENT_BINARY_DIR}/brecd;${CMAKE_CURRENT_SOURCE_DIR}/breye1d;${CMAKE_CURRENT_BINARY_DIR}/breye1d" CACHE STATIC "Brown University development package include files" FORCE)

set(BRLD_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(BRLD_SOURCE_DIR "${vxd_SOURCE_DIR}/contrib/brld")
set(BRLD_INSTALL_INCLUDE_DIR 
  ${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brld 
  ${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brld/bbasd 
  ${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brld/bmvgd 
  ${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brld/breye1d
  CACHE INTERNAL "Brown University development package include files"
)

# Location of brld's private FindXXX.cmake CMake modules.
#set( BRLD_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR}/bmodsd )
# This is identical to BRLD_CMAKE_DIR.  Perhaps we should eliminate BRLD_MODULE_PATH?
#set( BRLD_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/bmodsd )

include_directories(${BRLD_INCLUDE_DIR})

# basic services package (basic stuff that may not readily aspire to be in vxl/core)
add_subdirectory(bbasd)

# Brown multiview geometry (vxd development version)
add_subdirectory(bmvgd)

# Brown Segmentation and Detection Libraries (vxd development version)
add_subdirectory(bsegd)

# Brown Recognition Libraries (vxd development version)
add_subdirectory(brecd)

option(BUILD_BREYE1D "Build Old Brown Eyes VXD" YES)
if(BUILD_BREYE1D)
  add_subdirectory(breye1d)
endif(BUILD_BREYE1D)

# 3rd party libraries
add_subdirectory(b3pd)
