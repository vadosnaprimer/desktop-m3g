#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include "libpng.hpp"
#include "data.hpp"
using namespace std;
using namespace m3g;


World* wld = 0;

void display(void)
{
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->render (wld);
  glutSwapBuffers();
}

void resize(int w, int h)
{
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->setViewport (0,0,w,h);
  Camera* cam = wld->getActiveCamera();
  cam->setPerspective (45, w/(float)h, 0.1, 100);
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow(argv[0]);
  glewInit ();

  float scale = 1;
  float bias[3] = {0,0,0};

  short xyz[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  VertexArray* positions = new VertexArray (4, 3, 2);
  positions->set (0, 4, xyz);
  VertexBuffer* vertices1 = new VertexBuffer;
  vertices1->setPositions (positions, scale, bias);
  vertices1->setDefaultColor (0xff4c4cb2);  // 0.3, 0.3, 0.7

  VertexBuffer* vertices2 = new VertexBuffer;
  vertices2->setPositions (positions, scale, bias);
  vertices2->setDefaultColor (0xff4cb2b2);  // 0.3, 0.7, 0.7

  int strips[1] = {4};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);
  Appearance* app = new Appearance;

  Mesh* mesh1 = new Mesh (vertices1, tris, app);
  mesh1->translate (1,0,0);

  Mesh* mesh2 = new Mesh (vertices2, tris, app);
  mesh2->translate (-1,0,0);
  
  Group* grp = new Group;
  grp->translate (0,0,-3);
  grp->addChild(mesh1);
  grp->addChild(mesh2);


  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (grp);

  cout << *wld << "\n";

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
