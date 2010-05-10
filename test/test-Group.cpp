#include <unittest++/UnitTest++.h>
#include <iostream>
#include <vector>
#include "Group.hpp"
using namespace std;
using namespace m3g;


TEST (Group_default_variables)
{
  Group* grp = new Group;

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


TEST (Group_pick)
{
  Group* grp = new Group;

  // 実装されてない
  
  delete grp;
}

TEST (Group_duplicate)
{
  // parent --> grp0 --> child
  Group* grp0   = new Group;
  Group* parent = new Group;
  Group* child  = new Group;
  parent->addChild (grp0);
  grp0->addChild (child);

  Group* grp1   = grp0->duplicate();

  // parent --> grp0 --> child
  //             | (duplicate)
  //      0 --> grp1 --> duplicated child

  CHECK_EQUAL (grp0->getChildCount(), grp1->getChildCount());

  CHECK_EQUAL ((Node*)parent, grp0->getParent());
  CHECK_EQUAL ((Node*)0, grp1->getParent());

  CHECK_EQUAL (child, grp0->getChild(0));
  CHECK       (child != grp1->getChild(0));

  CHECK_EQUAL (grp1, grp1->getChild(0)->getParent());

  delete parent;
  delete child;
  delete grp0;
  delete grp1;
}
