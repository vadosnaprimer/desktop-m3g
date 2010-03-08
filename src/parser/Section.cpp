#include "adler32.hpp"
#include "Section.hpp"
#include "adler32.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
using namespace m3g;

bool Section:: compressed;
int  Section:: total_section_length;
int  Section:: uncompressed_length;
int  Section:: object_type;
int  Section:: object_length;
int  Section:: checksum;
char* Section:: buf = 0;

/**
 * 戻り値はオブジェクトの先頭を指す。
 * 現在は非圧縮のみ対応。
 */
void* Section:: parse (ifstream* ifs)
{
  ifs->read ((char*)&compressed, 1);
  ifs->read ((char*)&total_section_length, 4);
  ifs->read ((char*)&uncompressed_length, 4);
  ifs->read ((char*)&object_type, 1);
  ifs->read ((char*)&object_length, 4);
  ifs->seekg (-14, ios::cur); 

  if (ifs->eof())
    return 0;

  /*
  cout << "----- section start -----\n";
  cout << "compressed = " << compressed << "\n";
  cout << "total_section_length = " << total_section_length << "\n";
  cout << "uncompressed_length = " << uncompressed_length << "\n";
  cout << "object_type = " << hex << object_type << dec << "\n";
  cout << "object_length = " << object_length << "\n";
  */

  if (buf)
    free (buf);

  buf = (char*)malloc (total_section_length-4);
  ifs->read ((char*)buf, total_section_length-4);
  ifs->read ((char*)&checksum, 4);

  int chsum = adler32 ((unsigned char*)buf, total_section_length-4);
  if (chsum != checksum) {
    cout << "Checksum error, this section is ignored.\n";
    cout << "checksum " << checksum << " <--> " << chsum << "\n";
    return 0;
  }

  /*
  cout << "----- section end   -----\n";
  */

  return buf+9;
}


