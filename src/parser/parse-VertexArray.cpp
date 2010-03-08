#include <strstream>
#include <iostream>
#include "../VertexArray.hpp"
#include "parse-Object3D.hpp"
#include "../m3gexcept.hpp"
using namespace std;
using namespace m3g;


void parse_VertexArray (istrstream& iss, vector<Object3D*>& objs)
{
  Object3D* dummy = new Object3D;
  parse_Object3D (iss, objs, dummy);

  unsigned char component_size;
  unsigned char component_count;
  unsigned char encoding;
  unsigned short vertex_count;
  iss.read ((char*)&component_size, 1);
  iss.read ((char*)&component_count, 1);
  iss.read ((char*)&encoding, 1);
  iss.read ((char*)&vertex_count, 2);

  VertexArray* varr = new VertexArray (vertex_count, component_count, component_size);

  *(Object3D*)varr = *dummy;
  delete dummy;

  //cout << "encoding = " << (int)encoding << "\n";
  //cout << "component_count = " << (int)component_count << "\n";
  //cout << "component_size = " << (int)component_size << "\n";
  //cout << "vertex_count = " << (int)vertex_count << "\n";

  if (component_size == 1) {
    char* vertex_values = new char[vertex_count*component_count];
    iss.read ((char*)vertex_values, vertex_count*component_count);
    if (encoding) {
      for (int i = component_count; i < vertex_count*component_count; i++) {
	vertex_values[i] += vertex_values[i-component_count];
      }
    }
    varr->set (0, vertex_count, vertex_values);
  }
  else if (component_size == 2) {
    short* vertex_values = new short[vertex_count*component_count];
    iss.read ((char*)vertex_values, 2*vertex_count*component_count);
    if (encoding) {
      for (int i = component_count; i < vertex_count*component_count; i++) {
	vertex_values[i] += vertex_values[i-component_count];
      }
    }
    varr->set (0, vertex_count, vertex_values);
    for (int i = 0; i < vertex_count; i++) {
      for (int j = 0; j < component_count; j++) {
	//cout << vertex_values[i*component_count+j] << ", ";
      }
      //cout << "\n";
    }
    //cout << "\n";

  } else {
    throw domain_error ("Invalid component size is specified in m3g file.");
  }

  /*  
  varr->print (cout);
  varr->Object3D::print (cout);
  */

  objs.push_back (varr);
}
