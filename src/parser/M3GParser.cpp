#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <strstream>
#include "M3GParser.hpp"
#include "Section.hpp"
#include "parse-AnimationController.hpp"
#include "parse-AnimationTrack.hpp"
#include "parse-Appearance.hpp"
#include "parse-Background.hpp"
#include "parse-Camera.hpp"
#include "parse-CompositingMode.hpp"
#include "parse-Group.hpp"
#include "parse-Image2D.hpp"
#include "parse-KeyframeSequence.hpp"
#include "parse-Light.hpp"
#include "parse-Material.hpp"
#include "parse-Mesh.hpp"
#include "parse-PolygonMode.hpp"
#include "parse-Texture2D.hpp"
#include "parse-TriangleStripArray.hpp"
#include "parse-World.hpp"
#include "parse-VertexArray.hpp"
#include "parse-VertexBuffer.hpp"
#include "../m3gdef.hpp"
#include "../m3ginternal.hpp"
#include "../Exception.hpp"
using namespace m3g;
using namespace std;

const char m3g_ident[12] = {0xAB,0x4A,0x53,0x52,0x31,0x38,0x34,0xBB,0x0D,0x0A,0x1A,0x0A};

M3GParser:: M3GParser (const char* name) : 
  object_type(0), object_length(0),
  major_version(0), minor_version(0), has_external_references(false),
  total_file_size(0), approximate_size(0)
{
  if (name == NULL) {
    throw NullPointException (__FILE__, __func__, "File name is NULL.");
  }
 
   ifs = new ifstream (name);
   if (!ifs) {
     throw IOException (__FILE__, __func__, "Can't open file, name=%s.", name);
   }

    char ident[12];
    ifs->read ((char*)&ident, 12);

    if (memcmp(ident, m3g_ident, 12) != 0) {
      throw IOException (__FILE__, __func__, "This file is not m3g format, name=%s.", name);
    }

    memset (authoring_field, 0, sizeof(authoring_field));
    memset (exref_uri, 0, sizeof(exref_uri));

  // 注意：m3gの規格でobject_indexは1から始まることになっているので
  // ここで0番目ににダミーを入れておく。see P257
    objs.reserve (16);
    objs.push_back ((Object3D*)0);
}

M3GParser:: ~M3GParser ()
{
  ifs->close ();
}


vector<Object3D*> M3GParser:: parse ()
{
  parse_header_section ();
  parse_exref_section  ();
  parse_object_section ();

  vector<Object3D*> ret;
  ret.reserve (objs.size());

  for (int i = 0; i < (int)objs.size(); i++) {
    if (objs[i]) {
      ret.push_back (objs[i]);
    }
  }

  return ret;
}

void M3GParser:: parse_header_section ()
{
  void* p = Section::parse (ifs);
  istrstream iss ((char*)p, Section::total_section_length-13);

  iss.read ((char*)&object_type,   1);
  iss.read ((char*)&object_length, 4);
  iss.read ((char*)&major_version, 1);
  iss.read ((char*)&minor_version, 1);
  iss.read ((char*)&has_external_references, 1);
  iss.read ((char*)&total_file_size,  4);
  iss.read ((char*)&approximate_size, 4);
  iss.read ((char*)&authoring_field, min(255,object_length-11));

  cout << "header object: \n";
  cout << "  object_type     = " << (int)object_type << "\n";
  cout << "  object_length   = " << object_length << "\n";
  cout << "  major_version   = " << major_version << "\n";
  cout << "  minor_version   = " << minor_version << "\n";
  cout << "  has_external_references = " << has_external_references << "\n";
  cout << "  total_file_size = " << total_file_size << "\n";
  cout << "  authoring_field = " << authoring_field << "\n";

  // 注意：headerもオブジェクトindexに数えるのでここでダミーを入れておく。
  objs.push_back ((Object3D*)0);
}

void M3GParser:: parse_exref_section ()
{
  if (!has_external_references)
    return;

  void* p = Section::parse (ifs);
  istrstream iss ((char*)p, Section::total_section_length-13);

  iss.read ((char*)&object_type, 1);
  iss.read ((char*)&object_length, 4);
  iss.read ((char*)&exref_uri, min(255,object_length));

  cout << "exref object: \n";
  cout << "  object_type   = " << (int)object_type << "\n";
  cout << "  object_length = " << object_length << "\n";
  cout << "  exref_uri     = " << exref_uri << "\n";

  // 注意：exrefもオブジェクトindexに数えるのでここでダミーを入れておく。
  objs.push_back ((Object3D*)0);
}

void M3GParser:: parse_object_section ()
{
  void* p;
  int s = 2;
  // each section
  while ((p = Section::parse (ifs)) != 0) {

    istrstream iss ((char*)p, Section::total_section_length-13);

    cout << "section: " << s++ << "\n";

    // each objects
    while (1) {
      iss.read ((char*)&object_type, 1);
      iss.read ((char*)&object_length, 4);
      
      if (iss.eof()) {
	break;
      }

      cout << "object " << objs.size() << ": \n";
      cout << "  object_type   = " << objtype_to_string(object_type) << "(" << (int)object_type << ")\n";
      cout << "  object_length = " << object_length << "\n";

      // 巨大switch分で分岐
      switch (object_type) {
      case OBJTYPE_ANIMATION_CONTROLLER: {
	parse_AnimationController (iss, objs);
	break;
      }
      case OBJTYPE_ANIMATION_TRACK: {
	parse_AnimationTrack (iss, objs);
	break;
      }
      case OBJTYPE_APPEARANCE: {
	parse_Appearance (iss, objs);
	break;
      }
      case OBJTYPE_BACKGROUND: {
	parse_Background (iss, objs);
	break;
      }
      case OBJTYPE_CAMERA: {
	parse_Camera (iss, objs);
	break;
      }
      case OBJTYPE_COMPOSITING_MODE: {
	parse_CompositingMode (iss, objs);
	break;
      }
      case OBJTYPE_GROUP: {
	parse_Group (iss, objs);
	break;
      }
      case OBJTYPE_IMAGE2D: {
	parse_Image2D (iss, objs);
	break;
      }
      case OBJTYPE_KEYFRAME_SEQUENCE: {
	parse_KeyframeSequence (iss, objs);
	break;
      }
      case OBJTYPE_LIGHT: {
	parse_Light (iss, objs);
	break;
      }
      case OBJTYPE_MATERIAL: {
	parse_Material (iss, objs);
	break;
      }
      case OBJTYPE_MESH: {
	parse_Mesh (iss, objs);
	break;
      }
      case OBJTYPE_POLYGON_MODE: {
	parse_PolygonMode (iss, objs);
	break;
      }
      case OBJTYPE_TEXTURE2D: {
	parse_Texture2D (iss, objs);
	break;
      }
      case OBJTYPE_TRIANGLE_STRIP_ARRAY: {
	parse_TriangleStripArray (iss, objs);
	break;
      }
      case OBJTYPE_VERTEX_ARRAY: {
	parse_VertexArray (iss, objs);
	break;
      }
      case OBJTYPE_VERTEX_BUFFER: {
	parse_VertexBuffer (iss, objs);
	break;
      }
      case OBJTYPE_WORLD: {
	parse_World (iss, objs);
	break;
      }
      default: {
	cout << "M3GParser: Unkwon objtype=" << (int)object_type << "\n";
	// 今だけ空読み
	char* buf = (char*)malloc(object_length);
	iss.read (buf, object_length);
	free (buf);
      }
      
      }
    }
  }
}


std::ostream& operator<< (std::ostream& out, const M3GParser& p)
{
  return out;
}
