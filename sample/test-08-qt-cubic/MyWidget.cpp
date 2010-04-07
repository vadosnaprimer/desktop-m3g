#include "m3g.hpp"
#include "MyWidget.hpp"
#include <GL/glu.h>
#include <iostream>
#include <cmath>
using namespace std;
using namespace m3g;

MyWidget:: MyWidget () : wld(0), cam(0)
{
}

MyWidget:: ~MyWidget ()
{
}

void MyWidget:: initializeGL ()
{
  cout << "initializeGL is called\n";
  cout << "version = " << glGetString (GL_VERSION) << "\n";
  glewInit ();

  wld = new World;

  cam = new Camera;
  cam->lookAt (0,0,5, 0,0,0, 0,1,0);
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  
  QImage img = convertToGLFormat (QImage ("yuzuki.png"));
  cout << "width = " << img.width() << "\n";
  cout << "height = " << img.height() << "\n";
  Image2D* bg_img = new Image2D (Image2D::RGBA, img.width(), img.height(), img.bits());

  Background* bg = new Background;
  bg->setColor (0xff0000ff);
  bg->setImage (bg_img);
  wld->setBackground (bg);

  short vertices[] = {1,-1,1,  1,1,1,  -1,-1,1,  -1,1,1,
                      -1,-1,-1,  -1,1,-1,  1,-1,-1,  1,1,-1,
                      -1,1,1,  -1,1,-1,  -1,-1,1,  -1,-1,-1};
  VertexArray* positions = new VertexArray (12, 3, 2);
  positions->set (0, 12, vertices);

  short coords[] = {1,0, 1,1, 0,0, 0,1, 1,0, 1,1, 0,0, 0,1,
                    1,0, 0,0, 1,1, 0,1};
  VertexArray* tex_coords = new VertexArray (12, 2, 2);
  tex_coords->set (0, 12, coords);
  
  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* cube_vertices = new VertexBuffer;
  cube_vertices->setPositions (positions, scale, bias);
  cube_vertices->setTexCoords (0, tex_coords, scale, bias);
  cube_vertices->setDefaultColor(0xff4c4cb2);

  int indices[6][4] = {{0,1,2,3},
                       {2,3,4,5},
                       {4,5,6,7},
                       {6,7,0,1},
                       {1,7,8,9},
                       {0,10,6,11}};
  int lengths[8][1] = {{4},{4},{4},{4},{4},{4}};
  int color[6] = {0xffffffff,
                  0xff7fff7f,
                  0xff7f7fff,
                  0xffffff7f,
                  0xffff7fff,
                  0xff7fffff};
  const char* tex_name[6] = {"moe.png",
                       "moe.png",
                       "moe.png",
                       "moe.png",
                       "moe.png",
                       "moe.png"};

  TriangleStripArray* cube_strips[6];
  Appearance*         cube_appears[6];
  for (int i = 0; i < 6; i++) {
    cube_strips[i]  = new TriangleStripArray(indices[i], 1, lengths[i]);
    Material* mat   = new Material;
    mat->setColor (Material::DIFFUSE, color[i]);
    QImage img = convertToGLFormat (QImage (tex_name[i]));
    Image2D* img2D = new Image2D (Image2D::RGBA, img.width(), img.height(), img.bits());
    Texture2D* tex = new Texture2D (img2D);
    cube_appears[i] = new Appearance;
    cube_appears[i]->setMaterial (mat);
    cube_appears[i]->setTexture (0, tex);
  }

  Mesh* cube = new Mesh (cube_vertices,
                         6, (IndexBuffer**)cube_strips,
                         6, (Appearance**)cube_appears);
  wld->addChild (cube);
}


void MyWidget:: resizeGL(int width, int height)
{
  cout << "resizeGL is called\n";
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->setViewport (0,0,width,height);
  cam->setPerspective (45, width/(float)height, 0.1, 100);
}

void MyWidget:: paintGL ()
{
  Graphics3D* g3d = Graphics3D:: getInstance();
  g3d->render (wld);
  cout << *wld << "\n";
}

void MyWidget:: mousePressEvent (QMouseEvent* event)
{
  cur_x = event->x();
  cur_y = event->y();
}

void MyWidget:: mouseMoveEvent (QMouseEvent* event)
{
  cout << "mouse move " << event << "\n";

  float dx = event->x() - cur_x;
  float dy = event->y() - cur_y;
  cout << "dx = " << dx << "\n";
  cout << "dy = " << dy << "\n";

  if (dx > 1) {
    cam->postRotate (-2, 0,1,0);
  } else if (dx < -1) {
    cam->postRotate (2, 0,1,0);
  }
  if (dy > 1) {
    cam->postRotate (-2, 1,0,0);
  } else if (dy < -1) {
    cam->postRotate (+2, 1,0,0);
  }

  cur_x = event->x();
  cur_y = event->y();

  updateGL();
}


