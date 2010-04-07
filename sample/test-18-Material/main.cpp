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
Light* lig = 0;

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


int animation_time = 0;

static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    exit(0);
  case 's': {
    lig->setMode (Light::SPOT);
    cout << "Swith to SPOT light.";
    break;
  }
  case 'o': {
    lig->setMode (Light::OMNI);
    cout << "Swith to OMNI light.";
    break;
  }
  case 'd': {
    lig->setMode (Light::DIRECTIONAL);
    cout << "Swith to OMNI light.";
    break;
  }
  case ' ':
    cout << "glut: Space, time = " << animation_time << "\n";
    wld->animate (animation_time);
    animation_time += 2;
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
  glewInit ();

  AnimationController* controller = new AnimationController;

  KeyframeSequence* keyframe_light_color = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
  float frame_light_color[4][3] = {{1,1,0}, {0,1,0}, {1,1,0}, {1,0,0}};
  keyframe_light_color->setKeyframe (0, 0,   frame_light_color[0]);
  keyframe_light_color->setKeyframe (1, 100, frame_light_color[1]);
  keyframe_light_color->setKeyframe (2, 200, frame_light_color[2]);
  keyframe_light_color->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_light_color->setValidRange (0, 2);
  keyframe_light_color->setDuration (200);

  AnimationTrack* animation_light_color = new AnimationTrack (keyframe_light_color, AnimationTrack::COLOR);
  animation_light_color->setController (controller);


  VertexArray* pos_array = new VertexArray (800, 3, 2);
  pos_array->set (0, 800, vertices3);
  VertexArray* norm_array = new VertexArray (800, 3, 1);
  norm_array->set (0, 800, normals1);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (pos_array, scale, bias);
  vbuf->setNormals (norm_array);
  vbuf->setDefaultColor (0xffffffff);

  int strips[20] = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40};
  TriangleStripArray* tris = new TriangleStripArray (0, 20, strips);

  Material* mat = new Material;
  mat->setColor (Material::EMISSIVE, 0x00000000);
  mat->setColor (Material::DIFFUSE,  0x00000000);
  mat->setColor (Material::SPECULAR, 0x00ff0000);
  mat->setShininess (10);

  Appearance* app = new Appearance;
  app->setMaterial (mat);

  Mesh* mesh = new Mesh (vbuf, tris, app);
  //mesh->translate (0,0,-10);

  cout << "hello world\n";

  Camera* cam = new Camera;
  cam->lookAt (0,20,20,
               0,0,0,
               0,1,0);

  lig = new Light;
  lig->setColor (0xffffffff);
  lig->setIntensity (3);
  lig->setMode (Light::OMNI);
  lig->translate (0,1,0);
  lig->addAnimationTrack (animation_light_color);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (lig);
  wld->addChild (mesh);


  cout << *wld << "\n";

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
