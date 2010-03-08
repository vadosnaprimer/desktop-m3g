
#include <iosfwd>


class Section
{
public:

  static void* parse (std::ifstream* ifs);

  static bool compressed;
  static int  total_section_length;
  static int  uncompressed_length;
  static int  object_type;
  static int  object_length;
  static int  checksum;
  static char* buf;
};



