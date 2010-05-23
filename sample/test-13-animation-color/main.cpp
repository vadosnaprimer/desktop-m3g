#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>
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
  Camera* cam = wld->getActiveCamera();
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

int world_time = 0;

static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':
    quit ();
  break;
  case ' ':
    cout << "main: time = " << world_time << "\n";
    wld->animate (world_time);
    world_time += 2;
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

  Camera* cam = new Camera;
  cam->lookAt (0,0,5, 0,0,0, 0,1,0);

  Background* bg = new Background;
  bg->setColor (0xff3f3f3f);

  VertexArray* positions = new VertexArray (4, 3, 2);
  short        position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  positions->set (0, 4, position_values);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vertices = new VertexBuffer;
  vertices->setPositions (positions, scale, bias);
  //vertices->setDefaultColor (0xff0000ff);

  int strips[1] = {4};
  int indices[4] = {0,1,2,3};
  TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

  CompositingMode* comp = new CompositingMode;
  comp->setBlending (CompositingMode::ALPHA);

  Material* mat = new Material;
  mat->setColor (Material::DIFFUSE, 0xff0000ff);

  Appearance* app = new Appearance;
  app->setCompositingMode (comp);
  app->setMaterial (mat);

  float frame0_alpha[] = {1};
  float frame1_alpha[] = {0.1};
  KeyframeSequence* keyframe_alpha = new KeyframeSequence (2, 1, KeyframeSequence::LINEAR);
  keyframe_alpha->setKeyframe (0, 0, frame0_alpha);
  keyframe_alpha->setKeyframe (1, 100, frame1_alpha);
  keyframe_alpha->setValidRange (0, 1);
  keyframe_alpha->setDuration (100);

  KeyframeSequence* keyframe_color = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
  float frame0_color[] = {0,0,1};
  float frame1_color[] = {1,0,0};
  float frame2_color[] = {0,0,1};
  keyframe_color->setKeyframe (0, 0, frame0_color);
  keyframe_color->setKeyframe (1, 100, frame1_color);
  keyframe_color->setKeyframe (2, 200, frame2_color);
  keyframe_color->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_color->setValidRange (0, 2);
  keyframe_color->setDuration (200);

  AnimationController* controller = new AnimationController;
  //controller->setActiveInterval (0, 1000);
  controller->setSpeed (0.5, 0);

  AnimationTrack* track_alpha = new AnimationTrack (keyframe_alpha, AnimationTrack::ALPHA);
  AnimationTrack* track_color = new AnimationTrack (keyframe_color, AnimationTrack::DIFFUSE_COLOR);
  track_alpha->setController (controller);
  track_color->setController (controller);

  //mat->addAnimationTrack (track_alpha);
  mat->addAnimationTrack (track_color);

  Mesh* mesh = new Mesh (vertices, tris, app);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->setBackground (bg);
  wld->addChild (mesh);

  cout << *wld << "\n";

  objs.push_back (cam);
  objs.push_back (bg);
  objs.push_back (positions);
  objs.push_back (tris);
  objs.push_back (comp);
  objs.push_back (mat);
  objs.push_back (app);
  objs.push_back (keyframe_alpha);
  objs.push_back (keyframe_color);
  objs.push_back (controller);
  objs.push_back (track_alpha);
  objs.push_back (track_color);
  objs.push_back (mesh);
  objs.push_back (wld);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
