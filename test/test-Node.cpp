#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Node.hpp"
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

  node->setAlignment (zref, Node::ORIGIN, yref, Node::ORIGIN);
  node->setAlphaFactor (0.5);
  node->setRenderingEnable (false);
  node->setPickingEnable (false);
  node->setScope (1);
  node->setParent (parent);

  CHECK_EQUAL ((Node*)parent, node->getParent());
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
