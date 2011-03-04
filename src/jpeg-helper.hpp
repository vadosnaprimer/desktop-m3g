
#ifndef __M3G_JPEG_HELPER_HPP__
#define __M3G_JPEG_HELPER_HPP__


#include "m3g/Config.hpp"
#ifdef USE_JPEG

#include <jpeglib.h>

namespace m3g {

/**
 *
 */
void jpeg_memory_src (j_decompress_ptr cinfo, const void* data, unsigned long len);


} // using namespace m3g {


#endif // USE_JPEG


#endif // __M3G_JPEG_HELPER_HPP__
