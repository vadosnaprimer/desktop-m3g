#include <strstream>
#include <iostream>
#include <vector>
#include "../Group.hpp"
#include "parse-Node.hpp"
using namespace std;
using namespace m3g;

void parse_Group (istrstream& iss, vector<Object3D*>& objs, Group* grp=NULL)
{
  if (grp == NULL) {
    grp = new Group;
  }

  parse_Node (iss, objs, grp);

  unsigned int children_count;
  iss.read ((char*)&children_count, 4);
  //cout << "children_count = " << children_count << "\n";
  //cout << "objs size = " << objs.size() << "\n";
  for (int i = 0; i < (int)children_count; i++) {
    unsigned int children_index;
    iss.read ((char*)&children_index, 4);
    //cout << "children index = " << children_index << "\n";
    Node* node = dynamic_cast<Node*>(objs.at(children_index));
    grp->addChild (node);
  }

  /*
  grp->print (cout);
  grp->Node::print (cout);
  grp->Transformable::print (cout);
  grp->Object3D::print (cout);
  */
}


