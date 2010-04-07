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
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  VertexArray* pos_array = new VertexArray (4, 3, 1);
  char vertices[] = {1,-1,0, 1,1,-5, -1,-1,0, -1,1,-5};
  pos_array->set (0, 4, vertices);

  VertexArray* color_array = new VertexArray (4, 3, 1);
  char colors[] = {127,127,127, 127,127,127, 127,127,127, 127,127,127};
  color_array->set (0, 4, (char*)colors);

  VertexArray* tex_coord_array = new VertexArray (4, 2, 1);
  char texs[] = {1,0, 1,1, 0,0, 0,1};
  tex_coord_array->set (0, 4, texs);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (pos_array, scale, bias);
  vbuf->setColors (color_array);
  vbuf->setTexCoords (0, tex_coord_array, scale, bias);
  vbuf->setTexCoords (1, tex_coord_array, scale, bias);
  
  int strips[2] = {3, 3};
  int indices[] = {0,1,2, 2,1,3};

  TriangleStripArray* tris = new TriangleStripArray (indices, 2, strips);

  int width, height;
  unsigned char* pixel;
  pixel = (unsigned char*)readpng ("yumemi.png", &width, &height);
  cout << "png = " << width << "x" << height << "\n";
  
  Image2D* img0    = new Image2D (Image2D::RGB, width, height, pixel);
  img0->write_ppm ("img0.ppm");
  Texture2D* tex0  = new Texture2D (img0);
  tex0->setBlending (Texture2D::FUNC_REPLACE);

  pixel = (unsigned char*)readpng ("onnanoko.png", &width, &height);
  cout << "png = " << width << "x" << height << "\n";

  Image2D* img1    = new Image2D (Image2D::RGBA, width, height, pixel);
  img1->write_ppm ("img1.ppm");
  Texture2D* tex1  = new Texture2D (img1);
  tex1->setBlending (Texture2D::FUNC_DECAL);

  PolygonMode* pmode = new PolygonMode;
  pmode->setWinding (PolygonMode::WINDING_CW);
  pmode->setCulling (PolygonMode::CULL_FRONT);
  pmode->setPerspectiveCorrectionEnable (false);

  cout << *pmode;

  Appearance* app = new Appearance;
  app->setTexture (0, tex0);
  app->setTexture (1, tex1);
  app->setPolygonMode (pmode);

  Mesh* mesh = new Mesh (vbuf, tris, app);
  mesh->translate (0,0,2);
  
  cout << "hello world\n";

  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (mesh);

  cout << *wld << "\n";




  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
