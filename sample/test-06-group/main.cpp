#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
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

int world_time = 0;

static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    exit(0);
  case ' ':
    cout << "glut: Space, time = " << world_time << "\n";
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
  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow(argv[0]);
  glewInit ();

  AnimationController* controller = new AnimationController;

  KeyframeSequence* keyframe_sequence1 = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
  float keyframes1[3][3] = {{1,0,0}, {0,0,0}, {1,0,0}};
  keyframe_sequence1->setKeyframe (0, 0,   keyframes1[0]);
  keyframe_sequence1->setKeyframe (1, 100, keyframes1[1]);
  keyframe_sequence1->setKeyframe (2, 200, keyframes1[2]);
  keyframe_sequence1->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_sequence1->setValidRange (0, 2);
  keyframe_sequence1->setDuration (200);

  KeyframeSequence* keyframe_sequence2 = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
  float keyframes2[3][3] = {{-1,0,0}, {0,0,0}, {-1,0,0}};
  keyframe_sequence2->setKeyframe (0, 0,   keyframes2[0]);
  keyframe_sequence2->setKeyframe (1, 100, keyframes2[1]);
  keyframe_sequence2->setKeyframe (2, 200, keyframes2[2]);
  keyframe_sequence2->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_sequence2->setValidRange (0, 2);
  keyframe_sequence2->setDuration (200);

  AnimationTrack* animation_track1 = new AnimationTrack (keyframe_sequence1, AnimationTrack::TRANSLATION);
  animation_track1->setController (controller);

  AnimationTrack* animation_track2 = new AnimationTrack (keyframe_sequence2, AnimationTrack::TRANSLATION);
  animation_track2->setController (controller);

  float scale = 1;
  float bias[3] = {0,0,0};

  short xyz[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  VertexArray* positions = new VertexArray (4, 3, 2);
  positions->set (0, 4, xyz);

  VertexBuffer* vertices1 = new VertexBuffer;
  vertices1->setPositions (positions, scale, bias);

  VertexBuffer* vertices2 = new VertexBuffer;
  vertices2->setPositions (positions, scale, bias);

  int strips[1] = {4};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

  Material* mat1 = new Material;
  mat1->setColor (Material::DIFFUSE, 0xcf4c4cb2);

  CompositingMode* cmode1 = new CompositingMode;
  cmode1->setBlending (CompositingMode::ALPHA);
  
  Material* mat2 = new Material;
  mat2->setColor (Material::DIFFUSE, 0xcf4cb2b2);

  CompositingMode* cmode2 = new CompositingMode;
  cmode2->setBlending (CompositingMode::ALPHA);

  Appearance* app1 = new Appearance;
  app1->setMaterial (mat1);
  app1->setCompositingMode (cmode1);

  Appearance* app2 = new Appearance;
  app2->setMaterial (mat2);
  app2->setCompositingMode (cmode2);

  Mesh* mesh1 = new Mesh (vertices1, tris, app1);
  mesh1->addAnimationTrack (animation_track1);
  mesh1->translate (1,0,0);

  Mesh* mesh2 = new Mesh (vertices2, tris, app2);
  mesh2->addAnimationTrack (animation_track2);
  mesh2->translate (-1,0,0);
  
  Group* grp = new Group;
  grp->translate (0,0,-3);
  grp->addChild(mesh1);
  grp->addChild(mesh2);


  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (grp);

  cout << *wld << "\n";

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
