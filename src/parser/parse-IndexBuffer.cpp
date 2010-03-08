#include <strstream>
#include <iostream>
#include "../IndexBuffer.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;

void parse_IndexBuffer (istrstream& iss, vector<Object3D*>& objs, IndexBuffer* ibuf)
{
  parse_Object3D (iss, objs, ibuf);

  // nothing to do.
}
