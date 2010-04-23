#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
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
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->setViewport (0,0,w,h);
  Camera* cam = wld->getActiveCamera();
  cam->setPerspective (45, w/(float)h, 0.1, 100);
}

int animation_time = 0;

static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    exit(0);
  case ' ':
    cout << "glut: Space, time = " << animation_time << "\n";
    wld->animate (animation_time);
    animation_time += 2;
  default:
    break;
  }
  glutPostRedisplay();
}


int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glewInit ();

  AnimationController* controller = new AnimationController;

  KeyframeSequence* keyframe_fovy = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
  float frame_fovy[3][1] = {{45}, {90}, {45}};
  keyframe_fovy->setKeyframe (0, 0,   frame_fovy[0]);
  keyframe_fovy->setKeyframe (1, 100, frame_fovy[1]);
  keyframe_fovy->setKeyframe (2, 200, frame_fovy[2]);
  keyframe_fovy->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_fovy->setValidRange (0, 2);
  keyframe_fovy->setDuration (200);

  AnimationTrack* animation_fovy = new AnimationTrack (keyframe_fovy, AnimationTrack::FIELD_OF_VIEW);
  animation_fovy->setController (controller);

  VertexArray* pos_array = new VertexArray (4, 3, 2);
  pos_array->set (0, 4, vertices1);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (pos_array, scale, bias);

  //int strips[20] = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40};
  int strips[1] = {4};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

  Material* mat = new Material;
  mat->setColor (Material::DIFFUSE, 0xff4c4cb2);  // 0.3, 0.3, 0.7

  Appearance* app = new Appearance;
  app->setMaterial (mat);

  Mesh* mesh = new Mesh (vbuf, tris, app);
  
  cout << "hello world\n";

  Camera* cam = new Camera;
  //cam->translate (0,0,10);
  cam->lookAt (0,0,50,
	0,0,0,
               0.1,1,0);       
  //Light* lig = new Light;
  cam->addAnimationTrack (animation_fovy);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (mesh);
  //  wld->addChild (lig);

  cout << *wld << "\n";

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
