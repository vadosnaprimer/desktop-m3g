#include <strstream>
#include <iostream>
#include "../TriangleStripArray.hpp"
#include "../Exception.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;

void parse_TriangleStripArray (istrstream& iss, vector<Object3D*>& objs)
{
  Object3D* dummy = new Object3D;
  parse_Object3D (iss, objs, dummy);

  // ignore IndexBuffer.

  unsigned char encoding;
  iss.read ((char*)&encoding, 1);

  int start_index;
  int indices_count;
  int* indices = 0;

  switch (encoding) {
  case 0: {
    iss.read ((char*)&start_index, 4);
    break;
  }
  case 1: {
    unsigned char c;
    iss.read ((char*)&c, 1);
    start_index = c;
    break;
  }
  case 2: {
    unsigned short s;
    iss.read ((char*)&s, 2);
    start_index = s;
    break;
  }
  case 128: {
    iss.read ((char*)&indices_count, 4);
    indices = new int[indices_count];
    iss.read ((char*)indices, 4*indices_count);
    break;
  }
  case 129: {
    iss.read ((char*)&indices_count, 4);
    indices = new int[indices_count];
    for (int i = 0; i < (int)indices_count; i++) {
      unsigned char c;
      iss.read ((char*)&c, 1);
      indices[i] = c;
    }
    break;
  }
  case 130: {
    iss.read ((char*)&indices_count, 4);
    indices = new int[indices_count];
    for (int i = 0; i < (int)indices_count; i++) {
      unsigned short s;
      iss.read ((char*)&s, 2);
      indices[i] = s;
    }
    break;
  }
  default: {
    throw InternalException (__FILE__, __func__, "Unknown encoding format of TriangleStripArray.");
  }
  }

  int strips_count;
  iss.read ((char*)&strips_count, 4);
  int* strips = new int[strips_count];
  iss.read ((char*)strips, 4*strips_count);
  
  TriangleStripArray* tri = NULL;

  switch (encoding) {
  case 0:
  case 1:
  case 2: {
    tri = new TriangleStripArray (start_index, strips_count, strips);
    break;
  }
  case 128:
  case 129:
  case 130: {
    tri = new TriangleStripArray (indices, strips_count, strips);
    break;
  }
  }

  /*
  tri->print (cout);
  tri->IndexBuffer::print (cout);
  tri->Object3D::print (cout);
  */

  objs.push_back (tri);
}

