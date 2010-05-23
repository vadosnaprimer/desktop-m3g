#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "libpng.hpp"
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
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

void quit ()
{
  for (int i = 0; i < (int)objs.size(); i++) {
    delete objs[i];
  }
  Graphics3D* g3d = Graphics3D::getInstance();
  delete g3d;
  exit (0);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    quit ();
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  Camera* cam = new Camera;
  cam->lookAt (0,0,5, 0,0,0, 0,1,0);

  Background* bg = new Background;
  bg->setColor (0xff3f3f3f);

  int width, height;
  char*  png = (char*)readpng ("moe-small.png", &width, &height);
  //cout << "png = " << width << "x" << height << "\n";

  Image2D* img = new Image2D (Image2D::RGB, width, height, png);
  delete png;

  CompositingMode* cmp = new CompositingMode;
  cmp->setDepthTestEnable (true);

  Appearance* app0 = new Appearance;
  app0->setLayer (6);
  app0->setCompositingMode (cmp);
  Sprite3D* spr0 = new Sprite3D (true, img, app0);
  spr0->translate (0.9,0.9,-2);

  Appearance* app1 = new Appearance;
  app1->setLayer (5);
  app1->setCompositingMode (cmp);
  Sprite3D* spr1 = new Sprite3D (true, img, app1);
  spr1->translate (0,0,-1);

  Appearance* app2 = new Appearance;
  app2->setLayer (4);  
  app2->setCompositingMode (cmp);
  Sprite3D* spr2 = new Sprite3D (true, img, app2);
  spr2->translate (-0.9,-0.9,0);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->setBackground (bg);
  wld->addChild (spr0);
  wld->addChild (spr1);
  wld->addChild (spr2);

  cout << *wld << "\n";

  objs.push_back (cam);
  objs.push_back (bg);
  objs.push_back (img);
  objs.push_back (cmp);
  objs.push_back (app0);
  objs.push_back (spr0);
  objs.push_back (app1);
  objs.push_back (spr1);
  objs.push_back (app2);
  objs.push_back (spr2);
  objs.push_back (wld);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
