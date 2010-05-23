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
  for (int i = 0; i < (int)objs.size(); i++) {
    delete objs[i];
  }
  Graphics3D* g3d = Graphics3D::getInstance();
  delete g3d;
}

void MyWidget:: initializeGL ()
{
  cout << "initializeGL is called\n";
  cout << "version = " << glGetString (GL_VERSION) << "\n";

  wld = new World;

  cam = new Camera;
  cam->lookAt (0,0,5, 0,0,0, 0,1,0);
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  
  QImage   bg_qimg   = convertToGLFormat (QImage ("yuzuki.png"));
  Image2D* bg_img    = new Image2D (Image2D::RGBA, bg_qimg.width(), bg_qimg.height(), bg_qimg.bits());

  Background* bg = new Background;
  bg->setColor (0xff0000ff);
  bg->setImage (bg_img);
  wld->setBackground (bg);

  QImage   cube_qimg = convertToGLFormat (QImage ("moe.png"));
  Image2D* cube_img  = new Image2D (Image2D::RGBA, cube_qimg.width(), cube_qimg.height(), cube_qimg.bits());

  short position_values[] = { 1,-1,1,  1,1,1,  -1,-1,1,  -1,1,1,
                             -1,-1,-1,  -1,1,-1,  1,-1,-1,  1,1,-1,
                             -1,1,1,  -1,1,-1,  -1,-1,1,  -1,-1,-1};
  VertexArray* positions = new VertexArray (12, 3, 2);
  positions->set (0, 12, position_values);

  short tex_coord_values[] = {1,0, 1,1, 0,0, 0,1, 1,0, 1,1, 0,0, 0,1,
                    1,0, 0,0, 1,1, 0,1};
  VertexArray* tex_coords = new VertexArray (12, 2, 2);
  tex_coords->set (0, 12, tex_coord_values);
  
  float scale   = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* cube_vertices = new VertexBuffer;
  cube_vertices->setPositions (positions, scale, bias);
  cube_vertices->setTexCoords (0, tex_coords, scale, bias);
  cube_vertices->setDefaultColor (0xff4c4cb2);
  
  int indices[24] = {0,1,2,3, 2,3,4,5, 4,5,6,7, 6,7,0,1, 1,7,8,9, 0,10,6,11};
  int strips [6]  = {4,4,4,4,4,4};
  TriangleStripArray* cube_strips = new TriangleStripArray (indices, 6, strips);

  Appearance*         cube_appears  = new Appearance;
  Material*           cube_material = new Material;
  Texture2D*          cube_texture  = new Texture2D (cube_img);
  cube_appears->setMaterial (cube_material);
  cube_appears->setTexture (0, cube_texture);

  Mesh* cube = new Mesh (cube_vertices, cube_strips, cube_appears);

  wld->addChild (cube);

  objs.push_back (wld);
  objs.push_back (cam);
  objs.push_back (bg_img);
  objs.push_back (bg);
  objs.push_back (positions);
  objs.push_back (tex_coords);
  objs.push_back (cube_vertices);
  objs.push_back (cube_strips);
  objs.push_back (cube_appears);
  objs.push_back (cube_material);
  objs.push_back (cube_img);
  objs.push_back (cube_texture);


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


