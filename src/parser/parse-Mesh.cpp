#include <strstream>
#include <iostream>
#include <cstdlib>
#include "../VertexBuffer.hpp"
#include "../Mesh.hpp"
#include "../IndexBuffer.hpp"
#include "../Appearance.hpp"
#include "parse-Node.hpp"
using namespace std;
using namespace m3g;

void parse_Mesh (istrstream& iss, vector<Object3D*>& objs)
{
  Node* dummy = new Node;
  parse_Node (iss, objs, dummy);

  VertexBuffer* vbuf = NULL;

  unsigned int vertex_buffer_index;
  iss.read ((char*)&vertex_buffer_index, 4);
  if (vertex_buffer_index > 0) {
    vbuf = dynamic_cast<VertexBuffer*>(objs.at(vertex_buffer_index));
  }

  unsigned int submesh_count;
  iss.read ((char*)&submesh_count, 4);

  IndexBuffer** ibufs = new IndexBuffer* [submesh_count];
  Appearance** apps   = new Appearance* [submesh_count];

  for (int i = 0; i < (int)submesh_count; i++) {
    int index_buffer_index;
    int appearance_index;
    iss.read ((char*)&index_buffer_index, 4);
    iss.read ((char*)&appearance_index, 4);
    ibufs[i] = dynamic_cast<IndexBuffer*>(objs.at(index_buffer_index));
    apps[i]  = dynamic_cast<Appearance*>(objs.at(appearance_index));
  }
  
  Mesh* mesh = new Mesh (vbuf, submesh_count, ibufs, submesh_count, apps);
  *(Node*)mesh = *dummy;

  delete ibufs;
  delete apps;

  mesh->print (cout);
  mesh->Node::print (cout);
  mesh->Transformable::print (cout);
  mesh->Object3D::print (cout);

  objs.push_back (mesh);
}

