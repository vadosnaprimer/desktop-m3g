#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Node.hpp"
#include "Group.hpp"
using namespace std;
using namespace m3g;


TEST (Node_default_variables)
{
  Node* node = new Node;

  CHECK_EQUAL (OBJTYPE_NODE, node->getObjectType());
  CHECK_EQUAL ((Node*)0, node->getParent());
  CHECK_EQUAL (true, node->isRenderingEnabled());
  CHECK_EQUAL (true, node->isPickingEnabled());
  CHECK_EQUAL (1.0f, node->getAlphaFactor());
  CHECK_EQUAL (-1, node->getScope());
  CHECK_EQUAL (Node::NONE, node->getAlignmentTarget(Node::Z_AXIS));
  CHECK_EQUAL ((Node*)0, node->getAlignmentReference(Node::Z_AXIS));
  CHECK_EQUAL (Node::NONE, node->getAlignmentTarget(Node::Y_AXIS));
  CHECK_EQUAL ((Node*)0, node->getAlignmentReference(Node::Y_AXIS));

  delete node;
}

TEST (Node_set_variables)
{
  Node* node = new Node;
  Node* zref = new Node;
  Node* yref = new Node;
  Node* parent = new Node;
  Group* grp = new Group;

  node->setAlignment (zref, Node::ORIGIN, yref, Node::ORIGIN);
  node->setAlphaFactor (0.5);
  node->setRenderingEnable (false);
  node->setPickingEnable (false);
  node->setScope (1);
  grp->addChild (node);
  //node->setParent (parent);

  //CHECK_EQUAL ((Node*)parent, node->getParent());
  CHECK_EQUAL (grp, node->getParent());
  CHECK_EQUAL (false, node->isRenderingEnabled());
  CHECK_EQUAL (false, node->isPickingEnabled());
  CHECK_EQUAL (0.5f, node->getAlphaFactor());
  CHECK_EQUAL (1, node->getScope());
  CHECK_EQUAL (Node::ORIGIN, node->getAlignmentTarget(Node::Z_AXIS));
  CHECK_EQUAL ((Node*)zref, node->getAlignmentReference(Node::Z_AXIS));
  CHECK_EQUAL (Node::ORIGIN, node->getAlignmentTarget(Node::Y_AXIS));
  CHECK_EQUAL ((Node*)yref, node->getAlignmentReference(Node::Y_AXIS));

  delete node;
  delete zref;
  delete yref;
  delete parent;
}



TEST (Node_duplicate)
{
  // TODO : 現在アライメントのチェックはしていない

  Node* node0 = new Node;
  Node* zref = new Node;
  Node* yref = new Node;
  Node* parent = new Node;
  Group* grp = new Group;

  node0->setAlignment (zref, Node::ORIGIN, yref, Node::ORIGIN);
  node0->setAlphaFactor (0.5);
  node0->setRenderingEnable (false);
  node0->setPickingEnable (false);
  node0->setScope (1);
  // node0のparentがセットされる
  grp->addChild (node0);

  Node* node1 = node0->duplicate();

  // duplicate()したNodeのparentはNULL！
  CHECK_EQUAL ((Node*)0, node1->getParent());

  CHECK_EQUAL (node0->isRenderingEnabled()               , node1->isRenderingEnabled());
  CHECK_EQUAL (node0->isPickingEnabled()                 , node1->isPickingEnabled());
  CHECK_EQUAL (node0->getAlphaFactor()                   , node1->getAlphaFactor());
  CHECK_EQUAL (node0->getScope()                         , node1->getScope());
  CHECK_EQUAL (node0->getAlignmentTarget(Node::Z_AXIS)   , node1->getAlignmentTarget(Node::Z_AXIS));
  CHECK_EQUAL (node0->getAlignmentReference(Node::Z_AXIS), node1->getAlignmentReference(Node::Z_AXIS));
  CHECK_EQUAL (node0->getAlignmentTarget(Node::Y_AXIS)   , node1->getAlignmentTarget(Node::Y_AXIS));
  CHECK_EQUAL (node0->getAlignmentReference(Node::Y_AXIS), node1->getAlignmentReference(Node::Y_AXIS));

  delete node0;
  delete node1;
  delete zref;
  delete yref;
  delete parent;
}
