#include <unittest++/UnitTest++.h>
#include <iostream>
#include <vector>
#include "m3g/Group.hpp"
using namespace std;
using namespace m3g;


TEST (Group_default_variables)
{
    Group* grp = new Group;

    CHECK_EQUAL (0, grp->getChildCount());

    delete grp;
}

TEST (Group_set_variables)
{
    Group* grp  = new Group;
    Node*  node = new Node;

    grp->addChild (node);
    CHECK_EQUAL (1, grp->getChildCount());
    CHECK_EQUAL (node, grp->getChild(0));

    grp->removeChild (node);
    CHECK_EQUAL (0, grp->getChildCount());

    delete node;
    delete grp;
}


TEST (Group_isDesendant) 
{
    Group* skeleton = new Group;
    Group* bone0 = new Group;
    Group* bone1 = new Group;
    Node*  node0 = new Node;
    Node*  node1 = new Node;

    skeleton->addChild (bone0);
    bone0->addChild (bone1);
    bone1->addChild (node0);

    CHECK_EQUAL (true, skeleton->isDescendant(skeleton));
    CHECK_EQUAL (true, skeleton->isDescendant(bone0));
    CHECK_EQUAL (true, skeleton->isDescendant(bone1));
    CHECK_EQUAL (true, skeleton->isDescendant(node0));
    CHECK_EQUAL (false, skeleton->isDescendant(node1));
}


TEST (Group_find)
{
    Group* skeleton = new Group;
    Group* bone0 = new Group;
    Group* bone1 = new Group;
    Group* bone2 = new Group;

    skeleton->addChild (bone0);
    skeleton->addChild (bone1);
    bone1->addChild (bone2);

    skeleton->setUserID (103);
    bone0->setUserID (100);
    bone1->setUserID (101);
    bone2->setUserID (102);

    CHECK_EQUAL (skeleton, skeleton->find (103));
    CHECK_EQUAL (bone0, skeleton->find (100));
    CHECK_EQUAL (bone1, skeleton->find (101));
    CHECK_EQUAL (bone2, skeleton->find (102));

    
    delete bone0;
    delete bone1;
    delete bone2;
    delete skeleton;
}

TEST (Group_getReferences)
{
    Group* skeleton = new Group;
    Group* bone0 = new Group;
    Group* bone1 = new Group;

    skeleton->addChild (bone0);
    skeleton->addChild (bone1);

    int n;
    Object3D* objs[2];

    n = skeleton->getReferences (objs);
    CHECK_EQUAL (2, n);
    CHECK_EQUAL (bone0, objs[0]);
    CHECK_EQUAL (bone1, objs[1]);
    
    delete bone0;
    delete bone1;
    delete skeleton;
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

