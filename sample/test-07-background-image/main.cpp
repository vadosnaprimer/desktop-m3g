#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
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
  Camera* cam = wld->getActiveCamera ();
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

int world_time = 0;

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    quit();
    break;
  case ' ':
    wld->animate (world_time);
    world_time += 5;
  default:
    break;
  }
  glutPostRedisplay();
}


int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  Image2D* img = dynamic_cast<Image2D*>(Loader::load ("mizugi.png")[0]);
  cout << *img << "\n";
  int width    = img->getWidth();
  int height   = img->getHeight();
  Background* bg  = new Background;
  bg->setImage (img);
  //bg->setCrop (0,0,width,height);
  bg->setColor (0xffff0000);
  bg->setImageMode (Background::REPEAT, Background::REPEAT);
  bg->setCrop (-width,-height,width*2,height*2);

  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->setBackground (bg);

  cout << *wld << "\n";

  objs.push_back (img);
  objs.push_back (bg);
  objs.push_back (cam);
  objs.push_back (wld);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
