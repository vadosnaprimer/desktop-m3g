#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include "libpng.hpp"
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

  int width, height;
  unsigned char* pixel = 0;

  pixel = (unsigned char*)readpng ("moe.png", &width, &height);
  cout << "png = " << width << "x" << height << "\n";

  Image2D*   img = new Image2D (Image2D::RGB, width, height, pixel);
  Background* bg = new Background;
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

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
