#include <iostream>
#include <cstdlib>
#include <memory>
#include <png.h>
using namespace std;

void* readpng (const char* name, int* width, int* height)
{
  png_structp png_ptr;
  png_infop info_ptr;

  FILE* fp = fopen (name, "rb");
  if (!fp) {
    cout << "Can't find file: " << name << "\n";
    return 0;
  }

  png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, 0, 0, 0);
  if (!png_ptr) {
    cout << "Can't create png struct\n";
    return 0;
  }
  
  info_ptr = png_create_info_struct (png_ptr);
  if (!info_ptr) {
    cout << "Can't create info struct\n";
    return 0;
  }
  
  if (setjmp (png_jmpbuf (png_ptr))) {
    png_destroy_read_struct (&png_ptr, &info_ptr, png_infopp_NULL);
    abort ();
  }

  png_init_io (png_ptr, fp);
	
	
  // Get data
  png_read_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);
  
    cout << "width = " << info_ptr->width << "\n";
    cout << "height = " << info_ptr->height << "\n";
    cout << "bit_depth = " << (int)info_ptr->bit_depth << "\n";
    cout << "pixel_depth = " << (int)info_ptr->pixel_depth << "\n";
    cout << "channels = " << (int)info_ptr->channels << "\n";
  	
  png_byte** row_pointers;
  row_pointers = png_get_rows(png_ptr, info_ptr);

  /*
  cout << "P3\n" << info_ptr->width << " " << info_ptr->height << "\n255\n";
  for (int y = 0; y < (int)info_ptr->height; y++) {
      for (int x = 0; x < (int)info_ptr->width; x++)
	{
	  cout << min((int)row_pointers[y][x*4+0], 255) << " ";
	  cout << min((int)row_pointers[y][x*4+1], 255) << " ";
	  cout << min((int)row_pointers[y][x*4+2], 255) << " ";
	}
      cout << "\n";
    }
  */

  int size = info_ptr->width * info_ptr->height * info_ptr->channels;
  cout << "size = " << size << " byte\n";

  unsigned char* img = (unsigned char*)malloc(size);
  unsigned char* p = img;
  for (int y = (int)info_ptr->height-1; y >= 0; y--) {
    memcpy (p, row_pointers[y], info_ptr->width * info_ptr->channels);
    p += info_ptr->width * info_ptr->channels;
  }


  *width = info_ptr->width;
  *height = info_ptr->height;

  png_destroy_read_struct (&png_ptr, &info_ptr, png_infopp_NULL);

  return img;
}
