#include "m3g.hpp"
#include "data.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
using namespace m3g;

/*
// 注意：通常のマトリックスパレットでは不十分。
// positionsのみscale,biasを考慮したマトリックスパレットで変換する
// ↓上半分0.5,下半分0.5で90度左に回転させた例
main: time = 0
scale = 0.001
bias  = 0, 0, 0
global_pose[0] = [ 1,0,0,0; 0,1,0,0; 0,0,1,0; 0,0,0,1 ]
global_pose[1] = [ -4.37114e-08,-1,0,0; 1,-4.37114e-08,0,10; 0,0,1,0; 0,0,0,1 ]
bind_pose[0].inverse = [ 1,0,0,0; 0,1,0,0; 0,0,1,0; 0,0,0,1 ]
bind_pose[1].inverse = [ 1,0,0,0; 0,1,0,-10; 0,0,1,0; 0,0,0,1 ]
matrix_palette[0] = [ 1,0,0,0; 0,1,0,0; 0,0,1,0; 0,0,0,1 ]
matrix_palette[1] = [ -4.37114e-08,-1,0,10; 1,-4.37114e-08,0,10; 0,0,1,0; 0,0,0,1 ]
mat = [ 0.001,0,0,0; 0,0.001,0,0; 0,0,0.001,0; 0,0,0,1 ]
mat_inv = [ 1000,0,0,0; 0,1000,0,0; 0,0,1000,0; 0,0,0,1 ]
positions_matrix_palette[0] = [ 1,0,0,0; 0,1,0,0; 0,0,1,0; 0,0,0,1 ]
positions_matrix_palette[1] = [ -4.37114e-08,-1,0,10000; 1,-4.37114e-08,0,10000; 0,0,1,0; 0,0,0,1 ]
*/


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
  Camera* cam = wld->getActiveCamera();
  cam->setPerspective (45, w/(float)h, 0.1, 100);
  glutPostRedisplay();
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

static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    quit ();
    break;
  case ' ':
    cout << "main: time = " << world_time << "\n";
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
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  Quaternion q0 ( 45, 0,0,1);
  Quaternion q1 (-45 , 0,0,1);
  Quaternion q2 ( 45, 0,0,1);
  KeyframeSequence* keyframe_sequence = new KeyframeSequence (3, 4, KeyframeSequence::SLERP);
  float keyframe_orientation[3][4]= {{q0.x, q0.y, q0.z, q0.w},
                                     {q1.x, q1.y, q1.z, q1.w},
                                     {q2.x, q2.y, q2.z, q2.w}};
  keyframe_sequence->setKeyframe   (0, 0,   keyframe_orientation[0]);
  keyframe_sequence->setKeyframe   (1, 100, keyframe_orientation[1]);
  keyframe_sequence->setKeyframe   (2, 200, keyframe_orientation[2]);
  keyframe_sequence->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_sequence->setValidRange (0, 2);
  keyframe_sequence->setDuration   (200);

  AnimationController* animation_controller = new AnimationController;
  AnimationTrack*      animation_track      = new AnimationTrack (keyframe_sequence, AnimationTrack::ORIENTATION);
  animation_track->setController (animation_controller);


  VertexArray* positions = new VertexArray (42, 3, 2);
  positions->set (0, 42, (short*)xyz);

  float scale   = 0.001;
  float bias[3] = {0,0,0};
  VertexBuffer* vertices = new VertexBuffer;
  vertices->setPositions (positions, scale, bias);
  
  int strips[1] = {42};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

  Appearance* app = new Appearance;

  Group* bone0 = new Group;
  Group* bone1 = new Group;
  bone1->translate (0,10,0);
  bone0->addChild (bone1);
  
  SkinnedMesh* mesh = new SkinnedMesh (vertices, tris, app, bone0);
  //mesh->addTransform (bone0, 1, 0, 21);
  //mesh->addTransform (bone1, 1, 21, 21);
#if 1
  mesh->addTransform (bone0, 10, 0, 18);
  mesh->addTransform (bone0, 8 , 18, 2 );
  mesh->addTransform (bone0, 6 , 20, 2 );
  mesh->addTransform (bone0, 4 , 22, 2 );
  mesh->addTransform (bone0, 2 , 24, 2 );
  mesh->addTransform (bone1, 2 , 18, 2 );
  mesh->addTransform (bone1, 4 , 20, 2 );
  mesh->addTransform (bone1, 6 , 22, 2 );
  mesh->addTransform (bone1, 8 , 24, 2 );
  mesh->addTransform (bone1, 10, 26, 16);
#endif

  bone1->postRotate (90, 0,0,1);

  bone1->addAnimationTrack (animation_track);

  Camera* cam = new Camera;
  cam->translate (0,10,50);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (mesh);

  cout << *wld << "\n";

  objs.push_back (keyframe_sequence);
  objs.push_back (animation_controller);
  objs.push_back (animation_track);
  objs.push_back (positions);
  objs.push_back (tris);
  objs.push_back (bone0);
  objs.push_back (bone1);
  objs.push_back (mesh);
  objs.push_back (cam);
  objs.push_back (wld);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
