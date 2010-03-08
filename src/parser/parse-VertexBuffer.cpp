#include <strstream>
#include <iostream>
#include "../VertexBuffer.hpp"
#include "../VertexArray.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;

void parse_VertexBuffer (istrstream& iss, vector<Object3D*>& objs)
{
  VertexBuffer* vbuf = new VertexBuffer;

  parse_Object3D (iss, objs, vbuf);

  unsigned char r,g,b,a;
  iss.read ((char*)&r, 1);
  iss.read ((char*)&g, 1);
  iss.read ((char*)&b, 1);
  iss.read ((char*)&a, 1);
  unsigned int positions_index;
  float bias[3];
  float scale;
  iss.read ((char*)&positions_index, 4);
  iss.read ((char*)&bias, 4*3);
  iss.read ((char*)&scale, 4);
  if (positions_index > 0) {
    VertexArray* pos = dynamic_cast<VertexArray*>(objs.at(positions_index));
    vbuf->setPositions (pos, scale, bias);
  }
  unsigned int normals_index;
  iss.read ((char*)&normals_index, 4);
  if (normals_index > 0) {
    VertexArray* norm = dynamic_cast<VertexArray*>(objs.at(normals_index));
    vbuf->setNormals (norm);
  }
  unsigned int colors_index;
  iss.read ((char*)&colors_index, 4);
  if (colors_index > 0) {
    VertexArray* col = dynamic_cast<VertexArray*>(objs.at(colors_index));
    vbuf->setColors (col);
  }

  unsigned int tex_coord_array_count;
  iss.read ((char*)&tex_coord_array_count, 4);
  for (int i = 0; i < (int)tex_coord_array_count; i++) {
    unsigned int tex_coords_index;
    float scale;
    float bias[3];
    iss.read ((char*)&tex_coords_index, 4);
    iss.read ((char*)&bias, 4*3);
    iss.read ((char*)&scale, 4);
    if (tex_coords_index > 0) {
      VertexArray* tex_coords = dynamic_cast<VertexArray*>(objs.at(tex_coords_index));
      vbuf->setTexCoords (i, tex_coords, scale, bias);
    }
  }

  /*
  vbuf->print (cout);
  vbuf->Object3D::print (cout);
  */

  objs.push_back (vbuf);
}
