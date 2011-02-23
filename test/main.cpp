#include <unittest++/UnitTest++.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

int main (int argc, char** argv)
{
    // OpenGLコンテキストの作成
    // glXXXはコンテキストがないと呼び出せない
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_RGBA);
    glutCreateWindow (0);

    return UnitTest::RunAllTests();
}
