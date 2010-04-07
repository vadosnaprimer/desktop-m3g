#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
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
  case 'Q':
  case '\033':
    /* ESC か q か Q をタイプしたら終了 */
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
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  AnimationController* controller_translation = new AnimationController;
  //controller->setActiveInterval (0, 1000);
  controller_translation->setSpeed (1, 0);
  AnimationController* controller_orientation = new AnimationController;
  controller_orientation->setSpeed (2, 0);
  
  Quaternion q0 (0, 0,1,0);
  Quaternion q1 (180, 0,1,0);
  Quaternion q2 (360, 0,1,0);
  KeyframeSequence* keyframe_mesh_translate = new KeyframeSequence (4, 3, KeyframeSequence::LINEAR);
  KeyframeSequence* keyframe_mesh_orientation = new KeyframeSequence (3, 4, KeyframeSequence::SLERP);
  float frame_mesh_translate[3][3]= {{0,0,0},
                                     {4,0,0},
                                     {-4,0,0}};
  float frame_mesh_orientation[3][4]= {{q0.x, q0.y, q0.z, q0.w},
                                     {q1.x, q1.y, q1.z, q1.w},
                                     {q2.x, q2.y, q2.z, q2.w}};
  keyframe_mesh_translate->setKeyframe (0, 0,   frame_mesh_translate[0]);
  keyframe_mesh_translate->setKeyframe (1, 100,  frame_mesh_translate[1]);
  keyframe_mesh_translate->setKeyframe (2, 300, frame_mesh_translate[2]);
  keyframe_mesh_translate->setKeyframe (3, 400, frame_mesh_translate[0]);
  keyframe_mesh_translate->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_mesh_translate->setValidRange (0, 3);
  keyframe_mesh_translate->setDuration (400);
  keyframe_mesh_orientation->setKeyframe (0, 0,   frame_mesh_orientation[0]);
  keyframe_mesh_orientation->setKeyframe (1, 100,  frame_mesh_orientation[1]);
  keyframe_mesh_orientation->setKeyframe (2, 200, frame_mesh_orientation[2]);
  keyframe_mesh_orientation->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_mesh_orientation->setValidRange (0, 2);
  keyframe_mesh_orientation->setDuration (200);

  AnimationTrack* animation_mesh_translate = new AnimationTrack (keyframe_mesh_translate, AnimationTrack::TRANSLATION);
  animation_mesh_translate->setController (controller_translation);
  AnimationTrack* animation_mesh_orientation = new AnimationTrack (keyframe_mesh_orientation, AnimationTrack::ORIENTATION);
  animation_mesh_orientation->setController (controller_orientation);

  Background* bg = new Background;
  bg->setColor (0xff7f7f7f);

  Camera* cam = new Camera;
  cam->lookAt (0,0,10,
               0,0,0,
               0,1,0);

  short pos[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  VertexArray* positions = new VertexArray (4, 3, sizeof(short));
  positions->set (0, 4, pos);

  VertexBuffer* vertices = new VertexBuffer;
  float scale = 1;
  float bias[3] = {0,0,0};
  vertices->setPositions (positions, scale, bias);
  vertices->setDefaultColor (0xff0000ff);

  int strips[1] = {4};
  int indices[4] = {0,1,2,3};
  TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

  Appearance* app = new Appearance;

  Mesh* mesh = new Mesh (vertices, tris, app);
  mesh->addAnimationTrack (animation_mesh_translate);
  mesh->addAnimationTrack (animation_mesh_orientation);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->setBackground (bg);
  wld->addChild (mesh);

  cout << *wld << "\n";

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
