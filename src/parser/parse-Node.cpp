#include <strstream>
#include <iostream>
#include "../Node.hpp"
#include "parse-Transformable.hpp"
#include "parse-Node.hpp"
#include "../m3gexcept.hpp"
using namespace std;
using namespace m3g;


void parse_Node (istrstream& iss, vector<Object3D*>& objs, Node* node)
{
  if (node == NULL) {
    throw null_point_error ("Node is NULL.");
  }

  parse_Transformable (iss, objs, node);

  bool enable_rendering;
  iss.read ((char*)&enable_rendering, 1);
  node->setRenderingEnable (enable_rendering);

  bool enable_picking;
  iss.read ((char*)&enable_picking, 1);
  node->setPickingEnable (enable_picking);

  unsigned char alpha_factor;
  iss.read ((char*)&alpha_factor, 1);
  node->setAlphaFactor (alpha_factor);

  unsigned int scope;
  iss.read ((char*)&scope, 4);
  node->setScope (scope);

  bool has_alignment;
  iss.read ((char*)&has_alignment, 1);
  if (has_alignment) {
    unsigned char z_target;
    unsigned char y_target;
    int z_reference_index;
    int y_reference_index;
    iss.read ((char*)&z_target, 1);
    iss.read ((char*)&y_target, 1);
    iss.read ((char*)&z_reference_index, 4);
    iss.read ((char*)&y_reference_index, 4);
    Node* z_ref = dynamic_cast<Node*>(objs[z_reference_index]);
    Node* y_ref = dynamic_cast<Node*>(objs[y_reference_index]);
    node->setAlignment (z_ref, z_target, y_ref, y_target);
  }

}
