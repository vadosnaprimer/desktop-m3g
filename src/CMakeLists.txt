#
# M3G compile config file.
#


# m3g srcs
file (GLOB M3G_SRCS *.cpp)

# m3g headers
file (GLOB M3G_HEADERS *.hpp)

# m3g target
add_library (m3g SHARED ${M3G_SRCS})

# installer
install (FILES ${M3G_HEADERS}  DESTINATION include/m3g)
install (TARGETS m3g LIBRARY DESTINATION lib)

# compile flags
set (CMAKE_CXX_FLAGS         "-Wall")
set (CMAKE_CXX_FLAGS_DEBUG   "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O2")
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# dependent libraries
include_directories   (${M3G_REQUIRED_INCLUDE_DIR})
target_link_libraries (m3g ${M3G_REQUIRED_LIBRARIES})

# dependent custom libraries
include_directories   (${M3G_READER_WRITER_INCLUDE_DIR})
link_directories      (${M3G_READER_WRITER_LINK_DIR})
target_link_libraries (m3g ${M3G_READER_WRITER_LIBRARY})



