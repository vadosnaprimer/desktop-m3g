#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
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


static void keyboard(unsigned char key, int x, int y)
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
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  VertexArray* positions         = new VertexArray (4, 3, 1);
  char         position_values[] = {1,-1,0, 1,1,-5, -1,-1,0, -1,1,-5};
  positions->set (0, 4, position_values);

  VertexArray*  colors         = new VertexArray (4, 3, 1);
  unsigned char color_values[] = {255,255,255, 255,255,255, 255,255,255, 255,255,255};
  colors->set (0, 4, (char*)color_values);

  VertexArray* tex_coords = new VertexArray (4, 2, 1);
  char tex_coord_values[] = {1,0, 1,1, 0,0, 0,1};
  tex_coords->set (0, 4, tex_coord_values);

  float scale   = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vertices = new VertexBuffer;
  vertices->setPositions (positions, scale, bias);
  vertices->setColors (colors);
  vertices->setTexCoords (0, tex_coords, scale, bias);
  vertices->setTexCoords (1, tex_coords, scale, bias);
  
  int strips[2] = {3, 3};
  int indices[] = {0,1,2, 2,1,3};

  TriangleStripArray* tris = new TriangleStripArray (indices, 2, strips);

  int width, height;
  char* png = (char*)readpng ("yumemi.png", &width, &height);
  //cout << "png = " << width << "x" << height << "\n";
  
  Image2D* img0    = new Image2D (Image2D::RGB, width, height, png);
  //img0->write_ppm ("img0.ppm");
  Texture2D* tex0  = new Texture2D (img0);
  tex0->setBlending (Texture2D::FUNC_REPLACE);
  free (png);

  png = (char*)readpng ("onnanoko.png", &width, &height);
  //cout << "png = " << width << "x" << height << "\n";

  Image2D* img1    = new Image2D (Image2D::RGBA, width, height, png);
  //img1->write_ppm ("img1.ppm");
  Texture2D* tex1  = new Texture2D (img1);
  tex1->setBlending (Texture2D::FUNC_DECAL);
  free (png);

  PolygonMode* pmode = new PolygonMode;
  pmode->setWinding (PolygonMode::WINDING_CW);
  pmode->setCulling (PolygonMode::CULL_FRONT);
  pmode->setPerspectiveCorrectionEnable (false);

  Appearance* app = new Appearance;
  app->setTexture (0, tex0);
  app->setTexture (1, tex1);
  app->setPolygonMode (pmode);

  Mesh* mesh = new Mesh (vertices, tris, app);
  mesh->translate (0,0,2);
  
  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (mesh);

  cout << *wld << "\n";

  objs.push_back (positions);
  objs.push_back (colors);
  objs.push_back (tex_coords);
  objs.push_back (vertices);
  objs.push_back (tris);
  objs.push_back (img0);
  objs.push_back (tex0);
  objs.push_back (img1);
  objs.push_back (tex1);
  objs.push_back (pmode);
  objs.push_back (app);
  objs.push_back (mesh);
  objs.push_back (cam);
  objs.push_back (wld);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
