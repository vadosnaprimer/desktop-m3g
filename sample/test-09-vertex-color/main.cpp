#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
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
  Camera* cam = wld->getActiveCamera ();
  cam->setPerspective (45, w/(float)h, 0.1, 100);
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow(argv[0]);
  glewInit ();

  VertexArray* position_values = new VertexArray (4, 3, 2);
  short vertices[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  position_values->set (0, 4, vertices);

  VertexArray* color_values = new VertexArray (4, 3, 1);
  char colors[] = {255,0,0, 0,255,0, 0,0,255, 255,255,255};
  color_values->set (0, 4, colors);

  float scale   = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (position_values, scale, bias);
  vbuf->setColors    (color_values);
  
  int strips[]  = {4};
  int indices[] = {0,1,2,3};
  TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

  Material* mat = new Material;
  mat->setVertexColorTrackingEnable (true);

  Appearance* app = new Appearance;
  app->setMaterial (mat);

  Mesh* mesh = new Mesh (vbuf, tris, app);

  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->setActiveCamera (cam);
  wld->addChild (cam);
  wld->addChild (mesh);

  cout << *wld << "\n";

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
