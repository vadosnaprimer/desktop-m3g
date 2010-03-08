#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Mesh.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Appearance.hpp"
using namespace std;
using namespace m3g;


TEST (Mesh_default_variables_1)
{
  VertexBuffer* vbuf = new VertexBuffer;
  IndexBuffer* ibuf[2] = {new IndexBuffer, new IndexBuffer};
  Appearance*  app[2]  = {new Appearance, new Appearance};
  Mesh* mesh = new Mesh (vbuf, 2, ibuf, 2, app);

  CHECK_EQUAL (OBJTYPE_MESH, mesh->getObjectType());
  CHECK_EQUAL (vbuf,    mesh->getVertexBuffer());
  CHECK_EQUAL (2,       mesh->getSubmeshCount());
  CHECK_EQUAL (ibuf[0], mesh->getIndexBuffer(0));
  CHECK_EQUAL (ibuf[1], mesh->getIndexBuffer(1));
  CHECK_EQUAL (app[0],  mesh->getAppearance(0));
  CHECK_EQUAL (app[1],  mesh->getAppearance(1));

  Appearance* app2 = new Appearance;
  mesh->setAppearance (0, app2);
  CHECK_EQUAL (app2, mesh->getAppearance(0));

  delete vbuf;
  delete ibuf[0];
  delete ibuf[1];
  delete app[0];
  delete app[1];
  delete mesh;
}


TEST (Mesh_default_variables_2)
{
  VertexBuffer* vbuf = new VertexBuffer;
  IndexBuffer* ibuf = new IndexBuffer;
  Appearance* app = new Appearance;
  Mesh* mesh = new Mesh (vbuf, ibuf, app);

  CHECK_EQUAL (vbuf, mesh->getVertexBuffer());
  CHECK_EQUAL (1,    mesh->getSubmeshCount());
  CHECK_EQUAL (ibuf, mesh->getIndexBuffer(0));
  CHECK_EQUAL (app,  mesh->getAppearance(0));


  Appearance* app2 = new Appearance;
  mesh->setAppearance (0, app2);
  CHECK_EQUAL (app2, mesh->getAppearance(0));

  delete vbuf;
  delete ibuf;
  delete app;
  delete mesh;
}

