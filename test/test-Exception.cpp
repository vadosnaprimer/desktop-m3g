#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Exception.hpp"
using namespace std;
using namespace m3g;

TEST (ArithmeticException)
{
  ArithmeticException e (__FILE__, __func__, "%s", "Lynette Bishop");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Lynette Bishop", e.what());

}

TEST (IllegalArgumentException)
{
  IllegalArgumentException e(__FILE__, __func__, "%s", "Perrine-H. Clostermann");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Perrine-H. Clostermann", e.what());
}

TEST (IllegalStateException)
{
    IllegalStateException e(__FILE__, __func__, "%s", "Minna-Dietlinde Wilcke");
    CHECK_EQUAL ("test-Exception.cpp:RunImpl Minna-Dietlinde Wilcke", e.what());
}

TEST (IndexOutOfBoundException)
{
  IndexOutOfBoundsException e(__FILE__, __func__, "%s", "Charlotte E. Yeager");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Charlotte E. Yeager", e.what());
}

TEST (IOException)
{
  IOException e(__FILE__, __func__, "%s", "Francesca Lucchini");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Francesca Lucchini", e.what());
}

TEST (NullPointException)
{
  NullPointException e(__FILE__, __func__, "%s", "Eila Ilmatar Juutilainen");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Eila Ilmatar Juutilainen", e.what());
}

TEST (SecurityException)
{
  SecurityException e(__FILE__, __func__, "%s", "Sanya V. Litvyak");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Sanya V. Litvyak", e.what());
}

TEST (OpenGLException)
{
  OpenGLException e(__FILE__, __func__, "%s", "Erica Hartmann");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Erica Hartmann", e.what());
}

TEST (NotImplementedException)
{
  NotImplementedException e(__FILE__, __func__, "%s", "Gertrud Barkhorn");
  CHECK_EQUAL ("test-Exception.cpp:RunImpl Gertrud Barkhorn", e.what());
}
