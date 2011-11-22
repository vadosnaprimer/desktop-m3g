# =================================
# M3G project config file.
# =================================

# project info
project (M3G)

# required cmake
cmake_minimum_required (VERSION 2.0)

# =================================
# Avairable options
# =================================
option (USE_GL    "Set ON, if you use OpenGL (default ON)"      ON )
option (USE_GL_ES "Set ON, if you use OpenGL ES (default OFF)"  OFF)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/src/m3g/Config.hpp.in
                ${CMAKE_CURRENT_BINARY_DIR}/src/m3g/Config.hpp)

# ================================
# Default Build is "Debug"
# ================================
if (NOT CMAKE_BUILD_TYPE)
    message (STATUS "Build type is not specified, then")
    message (STATUS "  set CMAKE_BUILD_TYPE=Debug")
    set (CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)
message (STATUS "Configuring m3g for ${CMAKE_BUILD_TYPE}...")

# for "Debug"
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message (STATUS "  set CMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/bin")
    set (CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

# for "Release"
if  (CMAKE_BUILD_TYPE STREQUAL "Release")
    # nothing
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# ==================================
# dependend libraries
# ==================================

# libz.so, libpng.so, libjpeg.so, ligGL.so
find_package (ZLIB   REQUIRED)
if (USE_GL)
  message (STATUS "Linking libGL.so ...")
  find_package (OpenGL REQUIRED)
endif (USE_GL)


set (M3G_REQUIRED_LIBRARIES
         ${ZLIB_LIBRARIES}
         ${OPENGL_LIBRARIES})
set (M3G_REQUIRED_INCLUDE_DIR 
         ${ZLIB_INCLUDE_DIR}
         ${OPENGL_INCLUDE_DIR})


# =============================
# project src
# =============================
add_subdirectory (src)


# ================================
# Confirm current configuration
# ================================
message (STATUS "Generating Config.hpp ...")
message (STATUS "USE_GL    = ${USE_GL}")
message (STATUS "USE_GL_ES = ${USE_GL_ES}")


