#include <cstdio>
#include <cstdlib>
#include "jpeglib.h"

// メモリソースからのJPEG展開用マネージャ
// 引用元: http://yarimit.blog.so-net.ne.jp/2005-06-03

typedef struct {
	struct jpeg_source_mgr pub;	/* public fields */
	JOCTET * buffer;
	unsigned long buffer_length;
} memory_source_mgr;
typedef memory_source_mgr *memory_src_ptr;

void memory_init_source (j_decompress_ptr cinfo)
{
}


boolean memory_fill_input_buffer (j_decompress_ptr cinfo)
{
	memory_src_ptr src = (memory_src_ptr) cinfo->src;

	src->buffer[0] = (JOCTET) 0xFF;
	src->buffer[1] = (JOCTET) JPEG_EOI;
	src->pub.next_input_byte = src->buffer;
	src->pub.bytes_in_buffer = 2;
	return TRUE;
}

void memory_skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
	memory_src_ptr src = (memory_src_ptr) cinfo->src;

	if (num_bytes > 0) {
		src->pub.next_input_byte += (size_t) num_bytes;
		src->pub.bytes_in_buffer -= (size_t) num_bytes;
	}
}

void memory_term_source (j_decompress_ptr cinfo)
{
}


void jpeg_memory_src (j_decompress_ptr cinfo, const void* data, unsigned long len)
{
	memory_src_ptr src;

	if (cinfo->src == NULL) {	/* first time for this JPEG object? */
		cinfo->src = (struct jpeg_source_mgr *)
		(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
		  sizeof(memory_source_mgr));
		src = (memory_src_ptr) cinfo->src;
		src->buffer = (JOCTET *)
		(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
		  len * sizeof(JOCTET));
	}

	src = (memory_src_ptr) cinfo->src;

	src->pub.init_source = memory_init_source;
	src->pub.fill_input_buffer = memory_fill_input_buffer;
	src->pub.skip_input_data = memory_skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
	src->pub.term_source = memory_term_source;

	src->pub.bytes_in_buffer = len;
	src->pub.next_input_byte = (JOCTET*)data;
}

