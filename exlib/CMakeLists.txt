
# project src

# m3g-reader-writer
add_subdirectory (m3g-reader-writer)
set (M3G_READER_WRITER_INCLUDE_DIR ${M3G_READER_WRITER_SOURCE_DIR}/src                             PARENT_SCOPE)
set (M3G_READER_WRITER_LINK_DIR    ${M3G_READER_WRITER_BINARY_DIR}/src                             PARENT_SCOPE)
set (M3G_READER_WRITER_LIBRARY     -Wl,-whole-archive libm3g-reader-writer.a -Wl,-no-whole-archive PARENT_SCOPE)

# jpeg-helper
add_subdirectory (jpeg-helper)
set (JPEG_HELPER_INCLUDE_DIR ${JPEG_HELPER_SOURCE_DIR}/src                             PARENT_SCOPE)
set (JPEG_HELPER_LINK_DIR    ${JPEG_HELPER_BINARY_DIR}/src                             PARENT_SCOPE)
set (JPEG_HELPER_LIBRARY     -Wl,-whole-archive libjpeg-helper.a -Wl,-no-whole-archive PARENT_SCOPE)

