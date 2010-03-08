#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Bone.hpp"
#include "Node.hpp"
using namespace std;
using namespace m3g;


TEST (Bone_default_variable)
{
  Node* node = new Node;
  Bone* bone = new Bone (node, 1.0, 1, 100);

  CHECK_EQUAL (node, bone->node);
  CHECK_EQUAL (0.f,  bone->getWeight(0));
  CHECK_EQUAL (1.f,  bone->getWeight(1));
  CHECK_EQUAL (1.f,  bone->getWeight(100));
  CHECK_EQUAL (0.f,  bone->getWeight(101));

  CHECK_EQUAL (1, bone->inv_bind_matrix.m[0][0]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[0][1]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[0][2]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[0][3]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[1][0]);
  CHECK_EQUAL (1, bone->inv_bind_matrix.m[1][1]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[1][2]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[1][3]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[2][0]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[2][1]);
  CHECK_EQUAL (1, bone->inv_bind_matrix.m[2][2]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[2][3]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[3][0]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[3][1]);
  CHECK_EQUAL (0, bone->inv_bind_matrix.m[3][2]);
  CHECK_EQUAL (1, bone->inv_bind_matrix.m[3][3]);

  Matrix mat1 (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
  bone->setInverseBindMatrix (mat1);
  
  Matrix mat2 = bone->getInverseBindMatrix();

  CHECK_EQUAL (mat1.m[0][0], mat2.m[0][0]);
  CHECK_EQUAL (mat1.m[1][3], mat2.m[1][3]);
  CHECK_EQUAL (mat1.m[2][0], mat2.m[2][0]);
}
