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
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  AnimationController* controller = new AnimationController;

  KeyframeSequence* keyframe_fog_far = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
  float frame_fog_far[3][1] = {{10}, {4}, {10}};
  keyframe_fog_far->setKeyframe (0, 0,   frame_fog_far[0]);
  keyframe_fog_far->setKeyframe (1, 100, frame_fog_far[1]);
  keyframe_fog_far->setKeyframe (2, 200, frame_fog_far[2]);
  keyframe_fog_far->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_fog_far->setValidRange (0, 2);
  keyframe_fog_far->setDuration (200);

  AnimationTrack* animation_fog_far = new AnimationTrack (keyframe_fog_far, AnimationTrack::FAR_DISTANCE);
  animation_fog_far->setController (controller);

  VertexArray* pos_array = new VertexArray (4, 3, 2);
  pos_array->set (0, 4, vertices1);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (pos_array, scale, bias);
  vbuf->setDefaultColor (0xff0000ff);

  int strips[1] = {4};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

  Fog* fog = new Fog;
  fog->setLinear (4, 10);
  fog->setColor (0x00ff0000);
  fog->addAnimationTrack (animation_fog_far);
  fog->setMode (Fog::LINEAR);

  Appearance* app = new Appearance;
  app->setFog (fog);

  Mesh* mesh1 = new Mesh (vbuf, tris, app);
  mesh1->translate (0,0,-1);

  Mesh* mesh2 = new Mesh (vbuf, tris, app);
  mesh2->translate (0,0,-2);

  Mesh* mesh3 = new Mesh (vbuf, tris, app);
  mesh3->translate (0,0,-3);

  Mesh* mesh4 = new Mesh (vbuf, tris, app);
  mesh4->translate (0,0,-4);

  Mesh* mesh5 = new Mesh (vbuf, tris, app);
  mesh5->translate (0,0,-5);

  Group* grp = new Group;
  grp->addChild(mesh1);
  grp->addChild(mesh2);
  grp->addChild(mesh3);
  grp->addChild(mesh4);
  grp->addChild(mesh5);

  Camera* cam = new Camera;
  cam->lookAt (3,0,3, 0,0,-2, 0,1,0);

  Background* bg = new Background;
  bg->setColor (0xff3f3f3f);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (grp);
  wld->setBackground (bg);


  cout << *wld << "\n";

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
