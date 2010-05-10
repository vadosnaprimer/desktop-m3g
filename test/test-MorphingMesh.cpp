#include <unittest++/UnitTest++.h>
#include <iostream>
#include "MorphingMesh.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "TriangleStripArray.hpp"
#include "Appearance.hpp"
#include "Group.hpp"
using namespace std;
using namespace m3g;

TEST (MorphingMesh_default_value)
{
  VertexArray*  varry         = new VertexArray (16, 3, 2);
  int           indices[]   = {0,1,2};
  int           strips[]    = {3};
  TriangleStripArray* tris  = new TriangleStripArray (indices, 1, strips);
  Appearance*   app         = new Appearance;

  float scale  = 1;
  float bias[] = {0,0,0};

  VertexBuffer* base_vertices = new VertexBuffer;
  base_vertices->setPositions (varry, scale, bias);
  VertexBuffer* target_vertices[2] = {base_vertices->duplicate (),
                                      base_vertices->duplicate ()};
  MorphingMesh*  mesh        = new MorphingMesh (base_vertices, 2, target_vertices, tris, app);

  CHECK_EQUAL (2, mesh->getMorphTargetCount());

  delete base_vertices;
  delete target_vertices[0];
  delete target_vertices[1];
  delete tris;
  delete app;
  delete mesh;
}


TEST (MorphingMesh_set_variable)
{
  VertexArray*  varry         = new VertexArray (16, 3, 2);
  int           indices[]   = {0,1,2};
  int           strips[]    = {3};
  TriangleStripArray* tris  = new TriangleStripArray (indices, 1, strips);
  Appearance*   app         = new Appearance;

  float scale  = 1;
  float bias[] = {0,0,0};

  VertexBuffer* base_vertices = new VertexBuffer;
  base_vertices->setPositions (varry, scale, bias);
  VertexBuffer* target_vertices[2] = {base_vertices->duplicate (),
                                      base_vertices->duplicate ()};
  MorphingMesh*  mesh        = new MorphingMesh (base_vertices, 2, target_vertices, tris, app);

  CHECK_EQUAL (2, mesh->getMorphTargetCount());
  
  float weights[3] = {1,2,998};
  mesh->setWeights(2, weights);

  float values[3] = {999,999,999};
  mesh->getWeights(values);
  
  CHECK_EQUAL (1.f,   values[0]);
  CHECK_EQUAL (2.f,   values[1]);
  CHECK_EQUAL (999.f, values[2]);

  delete base_vertices;
  delete target_vertices[0];
  delete target_vertices[1];
  delete tris;
  delete app;
  delete mesh;
}

TEST (MorphingMesh_duplicate)
{
  VertexArray*  varry         = new VertexArray (16, 3, 2);
  int           indices[]   = {0,1,2};
  int           strips[]    = {3};
  TriangleStripArray* tris  = new TriangleStripArray (indices, 1, strips);
  Appearance*   app         = new Appearance;

  float scale  = 1;
  float bias[] = {0,0,0};

  VertexBuffer* base_vertices = new VertexBuffer;
  base_vertices->setPositions (varry, scale, bias);
  VertexBuffer* target_vertices[2] = {base_vertices->duplicate (),
                                      base_vertices->duplicate ()};
  MorphingMesh*  mesh1        = new MorphingMesh (base_vertices, 2, target_vertices, tris, app);

  float weights[2] = {1,2};
  mesh1->setWeights(2, weights);

  MorphingMesh* mesh2 = mesh1->duplicate();

  CHECK_EQUAL (2, mesh2->getMorphTargetCount());

  float values[3] = {999,999};
  mesh2->getWeights(values);

  CHECK_EQUAL (1.f,   values[0]);
  CHECK_EQUAL (2.f,   values[1]);


  delete base_vertices;
  delete target_vertices[0];
  delete target_vertices[1];
  delete tris;
  delete app;
  delete mesh1;
  delete mesh2;
}

