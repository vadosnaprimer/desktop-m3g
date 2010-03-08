#include <unittest++/UnitTest++.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
using namespace std;

int main (int argc, char** argv)
{
  // OpenGLコンテキストの作成
  // glXXXはコンテキストがないと呼び出せない
  glutInit (&argc,argv);
  glutInitDisplayMode (GLUT_RGBA);
  glutCreateWindow (0);
  glewInit();

  return UnitTest::RunAllTests();
}
