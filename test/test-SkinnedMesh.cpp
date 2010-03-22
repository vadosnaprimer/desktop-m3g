#include <unittest++/UnitTest++.h>
#include <iostream>
#include "SkinnedMesh.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "TriangleStripArray.hpp"
#include "Appearance.hpp"
#include "Group.hpp"
#include "Bone.hpp"
using namespace std;
using namespace m3g;


TEST (SkinnedMesh_default_variables)
{
  VertexBuffer* vbuf    = new VertexBuffer;
  int indices[] = {0,1,2};
  int strips[] = {3};
  TriangleStripArray* tris[2] = {new TriangleStripArray (indices, 1, strips),
                                  new TriangleStripArray (indices, 1, strips)};
  Appearance*  app[2]   = {new Appearance, new Appearance};
  Group*       skeleton = new Group;
  SkinnedMesh* mesh     = new SkinnedMesh (vbuf, 2, (IndexBuffer**)tris, 2, app, skeleton);


  CHECK_EQUAL (OBJTYPE_SKINNED_MESH, mesh->getObjectType());
  CHECK_EQUAL (skeleton, mesh->getSkeleton());

  delete vbuf;
  delete tris[0];
  delete tris[1];
  delete app[0];
  delete app[1];
  delete skeleton;
  delete mesh;
}

TEST (SkinnedMesh_addTransform)
{
  VertexBuffer* vbuf    = new VertexBuffer;
  int indices[] = {0,1,2};
  int strips[] = {3};
  TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);
  Appearance*  app      = new Appearance;
  Group*       root   = new Group;
  root->translate (0,0,2);
  Group*       bone_1 = new Group;
  bone_1->translate (0,3,0);
  root->addChild (bone_1);
  SkinnedMesh* mesh     = new SkinnedMesh (vbuf, tris, app, root);

  root->Transformable::print(cout);

  mesh->addTransform (root, 1, 0, 10);
  mesh->addTransform (bone_1, 1, 0, 10);

  CHECK_EQUAL (2, mesh->bones.size());
  
  Bone* bone;
  Matrix mat;

  bone = mesh->bones[0];
  CHECK_EQUAL (root, bone->node);

  mat = bone->getInverseBindMatrix();
  CHECK_CLOSE (1.f, mat.m[0][0], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[0][1], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[0][2], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[0][3], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[1][0], 0.00001f);
  CHECK_CLOSE (1.f, mat.m[1][1], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[1][2], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[1][3], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[2][0], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[2][1], 0.00001f);
  CHECK_CLOSE (1.f, mat.m[2][2], 0.00001f);
  CHECK_CLOSE (-2.f, mat.m[2][3], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[3][0], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[3][1], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[3][2], 0.00001f);
  CHECK_CLOSE (1.f, mat.m[3][3], 0.00001f);

  bone = mesh->bones[1];
  CHECK_EQUAL (bone_1, bone->node);

  mat = bone->getInverseBindMatrix();
  CHECK_CLOSE (1.f, mat.m[0][0], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[0][1], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[0][2], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[0][3], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[1][0], 0.00001f);
  CHECK_CLOSE (1.f, mat.m[1][1], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[1][2], 0.00001f);
  CHECK_CLOSE (-3.f, mat.m[1][3], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[2][0], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[2][1], 0.00001f);
  CHECK_CLOSE (1.f, mat.m[2][2], 0.00001f);
  CHECK_CLOSE (-2.f, mat.m[2][3], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[3][0], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[3][1], 0.00001f);
  CHECK_CLOSE (0.f, mat.m[3][2], 0.00001f);
  CHECK_CLOSE (1.f, mat.m[3][3], 0.00001f);

  //cout << "mat = " << mat << "\n";
}

TEST (SkinnedMesh_getBoneVertices_1)
{
  VertexArray* positions = new VertexArray (10, 3, 2);
  VertexBuffer* vbuf    = new VertexBuffer;
  float scale = 1;
  float bias[3] = {0,0,0};
  vbuf->setPositions (positions, scale, bias);
  int tri_indices[] = {0,1,2};
  int strips[] = {3};
  TriangleStripArray* tris = new TriangleStripArray (tri_indices, 1, strips);
  Appearance*  app      = new Appearance;
  Group*       root   = new Group;
  SkinnedMesh* mesh     = new SkinnedMesh (vbuf, tris, app, root);

  mesh->addTransform (root, 2, 0, 10);

  int n;
  int indices[10];
  float weights[10];

  n = mesh->getBoneVertices (root, NULL, NULL);

  CHECK_EQUAL (10, n);

  mesh->getBoneVertices (root, indices, weights);

  CHECK_EQUAL (0, indices[0]);
  CHECK_EQUAL (9, indices[9]);
  CHECK_EQUAL (1.f, weights[0]);
  CHECK_EQUAL (1.f, weights[9]);

  mesh->addTransform (root, 4, 5, 5);
  mesh->getBoneVertices (root, indices, weights);

  CHECK_EQUAL (0, indices[0]);
  CHECK_EQUAL (9, indices[9]);
  CHECK_EQUAL (1.f, weights[0]);
  CHECK_EQUAL (1.f, weights[9]);


  
}


TEST (SkinnedMesh_getBoneVertices_2)
{
  VertexArray* positions = new VertexArray (10, 3, 2);
  VertexBuffer* vbuf    = new VertexBuffer;
  float scale = 1;
  float bias[3] = {0,0,0};
  vbuf->setPositions (positions, scale, bias);
  int tri_indices[] = {0,1,2};
  int strips[] = {3};
  TriangleStripArray* tris = new TriangleStripArray (tri_indices, 1, strips);
  Appearance*  app      = new Appearance;
  Group*       root   = new Group;
  Group*       bone_1   = new Group;
  root->addChild (bone_1);
  SkinnedMesh* mesh     = new SkinnedMesh (vbuf, tris, app, root);

  mesh->addTransform (root, 1, 0, 6);
  mesh->addTransform (bone_1, 2, 4, 6);

  int n;
  int indices[10];
  float weights[10];

  n = mesh->getBoneVertices (root, NULL, NULL);

  CHECK_EQUAL (6, n);

  mesh->getBoneVertices (root, indices, weights);

  CHECK_EQUAL (0, indices[0]);
  CHECK_EQUAL (5, indices[5]);
  CHECK_CLOSE (1.f,       weights[0], 0.00001f);
  CHECK_CLOSE (1.f,       weights[3], 0.00001f);
  CHECK_CLOSE (0.333333f, weights[4], 0.00001f);
  CHECK_CLOSE (0.333333f, weights[5], 0.00001f);

  mesh->getBoneVertices (bone_1, indices, weights);

  CHECK_EQUAL (4, indices[0]);
  CHECK_EQUAL (9, indices[5]);
  CHECK_CLOSE (0.666667f, weights[0], 0.00001f);
  CHECK_CLOSE (0.666667f, weights[1], 0.00001f);
  CHECK_CLOSE (1.f,       weights[2], 0.00001f);
  CHECK_CLOSE (1.f,       weights[5], 0.00001f);
  
}


