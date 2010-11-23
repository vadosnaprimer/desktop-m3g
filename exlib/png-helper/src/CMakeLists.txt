
# png-helper srcs
file (GLOB PNG_HELPER_SRCS *.cpp)

# png-helper headers
file (GLOB PNG_HELPER_HEADERS *.hpp)

# png-helper target
add_library (png-helper STATIC ${PNG_HELPER_SRCS})


# installer
install (FILES ${PNG_HELPER_HEADERS}  DESTINATION include/m3g)
install (TARGETS png-helper ARCHIVE DESTINATION lib)


# compile flags
set (CMAKE_CXX_FLAGS         "-Wall -fPIC")
set (CMAKE_CXX_FLAGS_DEBUG   "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O2")
set (CMAKE_INCLUDE_CURRENT_DIR ON)


