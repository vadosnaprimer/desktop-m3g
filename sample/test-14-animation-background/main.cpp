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

  AnimationController* controller = new AnimationController;
  //controller->setActiveInterval (0, 1000);
  controller->setSpeed (1, 0);

  KeyframeSequence* keyframe_bg_color = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
  KeyframeSequence* keyframe_bg_alpha = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
  KeyframeSequence* keyframe_vbuf_color = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
  KeyframeSequence* keyframe_vbuf_alpha = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
  KeyframeSequence* keyframe_mat_color = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
  KeyframeSequence* keyframe_mat_alpha = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
  float frame_bg_color[3][3]= {{0.5,0.5,0.5},
                               {0.1,0.1,0.1},
                               {0.5,0.5,0.5}};
  float frame_bg_alpha[3][1] = {{1}, {0}, {1}};
  float frame_vbuf_color[3][3]= {{0,0,1},
                                 {1,0,0},
                                 {0,0,1}};
  float frame_vbuf_alpha[3][1] = {{1}, {0}, {1}};
  float frame_mat_color[3][3]= {{0,1,1},
                                 {1,1,0},
                                 {0,1,1}};
  float frame_mat_alpha[3][1] = {{0.2}, {0.5}, {0.2}};
  keyframe_bg_color->setKeyframe (0, 0,   frame_bg_color[0]);
  keyframe_bg_color->setKeyframe (1, 100, frame_bg_color[1]);
  keyframe_bg_color->setKeyframe (2, 200, frame_bg_color[2]);
  keyframe_bg_color->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_bg_color->setValidRange (0, 2);
  keyframe_bg_color->setDuration (200);
  keyframe_bg_alpha->setKeyframe (0, 0,   frame_bg_alpha[0]);
  keyframe_bg_alpha->setKeyframe (1, 100, frame_bg_alpha[1]);
  keyframe_bg_alpha->setKeyframe (2, 200, frame_bg_alpha[2]);
  keyframe_bg_alpha->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_bg_alpha->setValidRange (0, 2);
  keyframe_bg_alpha->setDuration (200);
  keyframe_vbuf_color->setKeyframe (0, 0,   frame_vbuf_color[0]);
  keyframe_vbuf_color->setKeyframe (1, 100, frame_vbuf_color[1]);
  keyframe_vbuf_color->setKeyframe (2, 200, frame_vbuf_color[2]);
  keyframe_vbuf_color->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_vbuf_color->setValidRange (0, 2);
  keyframe_vbuf_color->setDuration (200);
  keyframe_vbuf_alpha->setKeyframe (0, 0,   frame_vbuf_alpha[0]);
  keyframe_vbuf_alpha->setKeyframe (1, 100, frame_vbuf_alpha[1]);
  keyframe_vbuf_alpha->setKeyframe (2, 200, frame_vbuf_alpha[2]);
  keyframe_vbuf_alpha->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_vbuf_alpha->setValidRange (0, 2);
  keyframe_vbuf_alpha->setDuration (200);
  keyframe_mat_color->setKeyframe (0, 0,   frame_mat_color[0]);
  keyframe_mat_color->setKeyframe (1, 100, frame_mat_color[1]);
  keyframe_mat_color->setKeyframe (2, 200, frame_mat_color[2]);
  keyframe_mat_color->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_mat_color->setValidRange (0, 2);
  keyframe_mat_color->setDuration (200);
  keyframe_mat_alpha->setKeyframe (0, 0,   frame_mat_alpha[0]);
  keyframe_mat_alpha->setKeyframe (1, 100, frame_mat_alpha[1]);
  keyframe_mat_alpha->setKeyframe (2, 200, frame_mat_alpha[2]);
  keyframe_mat_alpha->setRepeatMode (KeyframeSequence::LOOP);
  keyframe_mat_alpha->setValidRange (0, 2);
  keyframe_mat_alpha->setDuration (200);

  AnimationTrack* animation_bg_color = new AnimationTrack (keyframe_bg_color, AnimationTrack::COLOR);
  animation_bg_color->setController (controller);
  AnimationTrack* animation_bg_alpha = new AnimationTrack (keyframe_bg_alpha, AnimationTrack::ALPHA);
  animation_bg_alpha->setController (controller);
  AnimationTrack* animation_vbuf_color = new AnimationTrack (keyframe_vbuf_color, AnimationTrack::COLOR);
  animation_vbuf_color->setController (controller);
  AnimationTrack* animation_vbuf_alpha = new AnimationTrack (keyframe_vbuf_alpha, AnimationTrack::ALPHA);
  animation_vbuf_alpha->setController (controller);
  AnimationTrack* animation_mat_color = new AnimationTrack (keyframe_mat_color, AnimationTrack::DIFFUSE_COLOR);
  animation_mat_color->setController (controller);
  AnimationTrack* animation_mat_alpha = new AnimationTrack (keyframe_mat_alpha, AnimationTrack::ALPHA);
  animation_mat_alpha->setController (controller);

  Background* bg = new Background;
  bg->setColor (0xff7f7f7f);
  bg->addAnimationTrack (animation_bg_color);
  bg->addAnimationTrack (animation_bg_alpha);

  Camera* cam = new Camera;
  cam->lookAt (0,0,5, 0,0,0, 0,1,0);


  short pos[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  VertexArray* positions = new VertexArray (4, 3, 2);
  positions->set (0, 4, pos);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vertices = new VertexBuffer;
  vertices->setPositions (positions, scale, bias);
  vertices->setDefaultColor (0xff0000ff);
  vertices->addAnimationTrack (animation_vbuf_color);
  vertices->addAnimationTrack (animation_vbuf_alpha);

  int strips[1] = {4};
  int indices[4] = {0,1,2,3};
  TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

  CompositingMode* comp = new CompositingMode;
  //comp->setBlending (CompositingMode::ALPHA);
  comp->setBlending (CompositingMode::REPLACE);


  Material* mat = new Material;
  mat->setColor (Material::DIFFUSE, 0xff00ffff);
  mat->addAnimationTrack (animation_mat_color);
  mat->addAnimationTrack (animation_mat_alpha);

  Appearance* app = new Appearance;
  app->setCompositingMode (comp);
  app->setMaterial (mat);


  Mesh* mesh = new Mesh (vertices, tris, app);


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
