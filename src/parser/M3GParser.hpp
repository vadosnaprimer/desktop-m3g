#ifndef __M3G_PARSER_HP__
#define __M3G_PARSER_HP__

#include <iosfwd>
#include <stdint.h>
#include <vector>

namespace m3g {
  class Object3D;

class M3GParser
{
public:
    M3GParser (const char* name);
    ~M3GParser ();

  std::vector<Object3D*> parse ();

private:
  void parse_header_section ();
  void parse_exref_section ();
  void parse_object_section ();

  std::ifstream* ifs;

  unsigned char  object_type;
  int  object_length;
  int  major_version;
  int  minor_version;
  bool has_external_references;
  int  total_file_size;
  int  approximate_size;
  char authoring_field[256];
  char exref_uri[256];

  std::vector<Object3D*> objs;
};


} // namespace m3g

std::ostream& operator<< (std::ostream& out, const m3g::M3GParser& parser);


#endif





