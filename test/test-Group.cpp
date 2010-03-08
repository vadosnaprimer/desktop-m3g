#include <unittest++/UnitTest++.h>
#include <iostream>
#include <vector>
#include "Group.hpp"
using namespace std;
using namespace m3g;


TEST (Group_default_variables)
{
  Group* grp = new Group;

  CHECK_EQUAL (OBJTYPE_GROUP, grp->getObjectType());
  CHECK_EQUAL (0, grp->getChildCount());
}

TEST (Group_set_variables)
{
  Group* grp = new Group;
  Node* node = new Node;
  grp->addChild (node);
  CHECK_EQUAL (1, grp->getChildCount());
  CHECK_EQUAL (node, grp->getChild(0));
  grp->removeChild (node);
  CHECK_EQUAL (0, grp->getChildCount());
  delete node;
  delete grp;
}

TEST (Group_findByType)
{
  Group* grp = new Group;
  Node* node1 = new Node;
  Node* node2 = new Node;

  grp->addChild (node1);
  grp->addChild (node2);

  vector<Object3D*> objs;

  grp->findByObjectType (OBJTYPE_NODE, objs);
  CHECK_EQUAL (2, objs.size());
  CHECK_EQUAL (node1, dynamic_cast<Node*>(objs[0]));
  CHECK_EQUAL (node2, dynamic_cast<Node*>(objs[1]));

  objs.clear();
  grp->findByObjectType (OBJTYPE_GROUP, objs);
  CHECK_EQUAL (1, objs.size());
  CHECK_EQUAL (grp, dynamic_cast<Group*>(objs[0]));

}

TEST (Group_pick)
{
  Group* grp = new Group;

  // 実装されてない
  
  delete grp;
}

