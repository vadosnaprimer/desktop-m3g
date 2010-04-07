#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
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
  float aspect_ratio = w/(float)h;
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->setViewport (0,0,w,h);
  Camera* cam = wld->getActiveCamera ();
  float angle = 45;
  float near  = 0.1;
  float far   = 100;
  float fovy = near * tan (angle/2.f) * 2;
  cam->setPerspective (fovy, aspect_ratio, near, far);
  cout << "fovy = " << fovy << "\n";
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow(argv[0]);
  glewInit ();

  VertexArray* pos_array = new VertexArray (800, 3, sizeof(short));
  pos_array->set (0, 800, vertices3);

  VertexBuffer* vbuf = new VertexBuffer;
  float scale = 1;
  float bias[3] = {0,0,0};
  vbuf->setPositions (pos_array, scale, bias);
  vbuf->setDefaultColor (0xffffffff);

  int strips[20] = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40};
  TriangleStripArray* tris = new TriangleStripArray (0, 20, strips);

  Material* mat = new Material;
  mat->setColor (Material::DIFFUSE, 0xffffffff);

  Appearance* app = new Appearance;
  app->setMaterial (mat);

  Mesh* mesh = new Mesh (vbuf, tris, app);
  //mesh->translate (0,0,-10);

  cout << "hello world\n";

  Camera* cam = new Camera;
  cam->lookAt (0,20,0,
               0,0,0,
               0,0,1);

  Light* lig = new Light;
  lig->setMode (Light::OMNI);
  lig->translate (0,1,0);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (lig);
  wld->addChild (mesh);


    cout << *wld << "\n";

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
