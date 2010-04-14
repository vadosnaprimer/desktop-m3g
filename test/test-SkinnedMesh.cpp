#include <unittest++/UnitTest++.h>
#include <iostream>
#include "SkinnedMesh.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "TriangleStripArray.hpp"
#include "Appearance.hpp"
#include "Group.hpp"
using namespace std;
using namespace m3g;

TEST (SkinnedMesh_default_variables)
{
  VertexArray*  varry       = new VertexArray (16, 3, 2);
  VertexBuffer* vbuf        = new VertexBuffer;
  int           indices[]   = {0,1,2};
  int           strips[]    = {3};
  TriangleStripArray* tris  = new TriangleStripArray (indices, 1, strips);
  Appearance*   app         = new Appearance;
  Group*        skeleton    = new Group;

  float scale  = 1;
  float bias[] = {0,0,0};
  vbuf->setPositions (varry, scale, bias);

  SkinnedMesh*  mesh        = new SkinnedMesh (vbuf, 1, (IndexBuffer**)&tris, 1, &app, skeleton);

  CHECK_EQUAL (OBJTYPE_SKINNED_MESH, mesh->getObjectType());
  CHECK_EQUAL (skeleton, mesh->getSkeleton());

  delete vbuf;
  delete tris;
  delete app;
  delete skeleton;
  delete mesh;
}


TEST (SkinnedMesh_getGlobalPose)
{
  // grp0 --> grp1 --> grp2
  Group* grp2 = new Group;
  Group* grp1 = new Group;
  Group* grp0 = new Group;
  grp0->addChild (grp1);
  grp1->addChild (grp2);

  Matrix global_pose;
  
  global_pose = SkinnedMesh:: getGlobalPose (grp2);
  CHECK_CLOSE (1, global_pose.m[0][0], 0.0001f);
  CHECK_CLOSE (1, global_pose.m[1][1], 0.0001f);
  CHECK_CLOSE (1, global_pose.m[2][2], 0.0001f);
  CHECK_CLOSE (1, global_pose.m[3][3], 0.0001f);
  CHECK_CLOSE (0, global_pose.m[0][1], 0.0001f);
  CHECK_CLOSE (0, global_pose.m[0][2], 0.0001f);
  CHECK_CLOSE (0, global_pose.m[0][3], 0.0001f);

  grp0->translate (0,0,1);
  global_pose = SkinnedMesh:: getGlobalPose (grp2);
  CHECK_CLOSE (1, global_pose.m[2][3], 0.0001f);


  grp1->translate (0,2,0);
  global_pose = SkinnedMesh:: getGlobalPose (grp2);
  CHECK_CLOSE (2, global_pose.m[1][3], 0.0001f);

  grp2->translate (3,0,0);
  global_pose = SkinnedMesh:: getGlobalPose (grp2);
  CHECK_CLOSE (3, global_pose.m[0][3], 0.0001f);
  
  cout << "global_pose = " << global_pose << "\n";
}

TEST (SkinnedMesh_addTransform_getBoneVertices)
{
  VertexArray*  varry       = new VertexArray (10, 3, 2);
  VertexBuffer* vbuf        = new VertexBuffer;
  int           indices[]   = {0,1,2};
  int           strips[]    = {3};
  TriangleStripArray* tris  = new TriangleStripArray (indices, 1, strips);
  Appearance*   app         = new Appearance;

  Group*        bone0    = new Group;
  Group*        bone1    = new Group;
  Group*        bone2    = new Group;
  bone1->translate (0,1,0);
  bone2->translate (1,0,0);
  bone0->addChild (bone1);
  bone0->addChild (bone2);

  float scale  = 1;
  float bias[] = {0,0,0};
  vbuf->setPositions (varry, scale, bias);

  SkinnedMesh*  mesh        = new SkinnedMesh (vbuf, 1, (IndexBuffer**)&tris, 1, &app, bone0);

  // vertices 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  // bone0    ----------        ----
  // bone1          ----------
  // bone2          ----                   
  mesh->addTransform (bone0, 100, 0, 4);
  mesh->addTransform (bone0, 100, 6, 2);
  mesh->addTransform (bone1, 100, 2, 4);
  mesh->addTransform (bone2, 20,  2, 2);  // ウェイトの小さな3つ目のボーンは無視
  
  int vertex_indices[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  float weights[10] = {0,0,0,0,0,0,0,0,0,0};
  int num = 0;

  num = mesh->getBoneVertices (bone0, vertex_indices, weights);
  CHECK_EQUAL (6, num);
  CHECK_EQUAL (0, vertex_indices[0]);
  CHECK_EQUAL (1, vertex_indices[1]);
  CHECK_EQUAL (2, vertex_indices[2]);
  CHECK_EQUAL (3, vertex_indices[3]);
  CHECK_EQUAL (6, vertex_indices[4]);
  CHECK_EQUAL (7, vertex_indices[5]);
  CHECK_CLOSE (1,   weights[0], 0.00001);
  CHECK_CLOSE (1,   weights[1], 0.00001);
  CHECK_CLOSE (0.5, weights[2], 0.00001);
  CHECK_CLOSE (0.5, weights[3], 0.00001);
  CHECK_CLOSE (1,   weights[4], 0.00001);
  CHECK_CLOSE (1,   weights[5], 0.00001);

  num = mesh->getBoneVertices (bone1, vertex_indices, weights);
  CHECK_EQUAL (4, num);
  CHECK_EQUAL (2, vertex_indices[0]);
  CHECK_EQUAL (3, vertex_indices[1]);
  CHECK_EQUAL (4, vertex_indices[2]);
  CHECK_EQUAL (5, vertex_indices[3]);
  CHECK_CLOSE (0.5, weights[0], 0.00001);
  CHECK_CLOSE (0.5, weights[1], 0.00001);
  CHECK_CLOSE (1,   weights[2], 0.00001);
  CHECK_CLOSE (1,   weights[3], 0.00001);

  num = mesh->getBoneVertices (bone2, vertex_indices, weights);
  CHECK_EQUAL (0, num);


}

TEST (SkinnedMesh_getBoneTransform)
{
  VertexArray*  varry       = new VertexArray (10, 3, 2);
  VertexBuffer* vbuf        = new VertexBuffer;
  int           indices[]   = {0,1,2};
  int           strips[]    = {3};
  TriangleStripArray* tris  = new TriangleStripArray (indices, 1, strips);
  Appearance*   app         = new Appearance;

  Group*        bone0    = new Group;
  Group*        bone1    = new Group;
  Group*        bone2    = new Group;
  bone1->translate (0,1,0);
  bone2->translate (1,0,0);
  bone0->addChild (bone1);
  bone0->addChild (bone2);

  float scale  = 1;
  float bias[] = {0,0,0};
  vbuf->setPositions (varry, scale, bias);

  SkinnedMesh*  mesh        = new SkinnedMesh (vbuf, 1, (IndexBuffer**)&tris, 1, &app, bone0);

  // vertices 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  // bone0    ----------        ----
  // bone1          ----------
  // bone2          ----                   
  mesh->addTransform (bone0, 100, 0, 4);
  mesh->addTransform (bone0, 100, 6, 2);
  mesh->addTransform (bone1, 100, 2, 4);
  mesh->addTransform (bone2, 20,  2, 2);  // ウェイトの小さな3つ目のボーンは無視

  Transform trns;
  float m[16];

  mesh->getBoneTransform (bone1, &trns);
  trns.get (m);
  CHECK_CLOSE (-1, m[7], 0.00001);   // m[1][3] = ty

  mesh->getBoneTransform (bone2, &trns);
  trns.get (m);
  CHECK_CLOSE (-1, m[3], 0.00001);   // m[0][3] = tx

  cout << trns << "\n";
}

TEST (SkinnedMesh_duplicate)
{
  VertexArray*  varry       = new VertexArray (10, 3, 2);
  VertexBuffer* vbuf        = new VertexBuffer;
  int           indices[]   = {0,1,2};
  int           strips[]    = {3};
  TriangleStripArray* tris  = new TriangleStripArray (indices, 1, strips);
  Appearance*   app         = new Appearance;

  Group*        bone0    = new Group;
  Group*        bone1    = new Group;
  Group*        bone2    = new Group;
  bone1->translate (0,1,0);
  bone2->translate (1,0,0);
  bone0->addChild (bone1);
  bone0->addChild (bone2);

  float scale  = 1;
  float bias[] = {0,0,0};
  vbuf->setPositions (varry, scale, bias);

  SkinnedMesh* mesh0 = new SkinnedMesh (vbuf, 1, (IndexBuffer**)&tris, 1, &app, bone0);

  // vertices 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  // bone0    ----------        ----
  // bone1          ----------
  // bone2          ----                   
  mesh0->addTransform (bone0, 100, 0, 4);
  mesh0->addTransform (bone0, 100, 6, 2);
  mesh0->addTransform (bone1, 100, 2, 4);
  mesh0->addTransform (bone2, 20,  2, 2);  // ウェイトの小さな3つ目のボーンは無視


  SkinnedMesh* mesh1  = mesh0->duplicate();

  CHECK (mesh0->getSkeleton() != mesh1->getSkeleton());
  CHECK_EQUAL (mesh0->getBoneVertices(bone0,0,0), mesh1->getBoneVertices(bone0,0,0));
  CHECK_EQUAL (mesh0->getBoneVertices(bone1,0,0), mesh1->getBoneVertices(bone1,0,0));
  CHECK_EQUAL (mesh0->getBoneVertices(bone2,0,0), mesh1->getBoneVertices(bone2,0,0));

}

