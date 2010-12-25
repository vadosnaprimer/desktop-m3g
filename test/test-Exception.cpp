#include <unittest++/UnitTest++.h>
#include <iostream>
#include <string.h>
#include "m3g/Exception.hpp"
using namespace std;
using namespace m3g;

/**
 * 返される文字列は「ファイル名:関数名 エラー文字列」
 * ファイル名は絶対パス(CMakeがg++に絶対パスで渡すから)なので
 * 比較対象からは外す。
 */

TEST (ArithmeticException)
{
    const char* str = "Lynette Bishop";
    ArithmeticException e (__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Lynette Bishop", e.what()+strlen(e.what())-strlen(str));
}

TEST (IllegalArgumentException)
{
    const char* str = "Perrine-H. Clostermann";
    IllegalArgumentException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Perrine-H. Clostermann", e.what()+strlen(e.what())-strlen(str));
}

TEST (IllegalStateException)
{
    const char* str = "Minna-Dietlinde Wilcke";
    IllegalStateException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Minna-Dietlinde Wilcke", e.what()+strlen(e.what())-strlen(str));
}

TEST (IndexOutOfBoundException)
{
    const char* str = "Charlotte E. Yeager";
    IndexOutOfBoundsException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Charlotte E. Yeager", e.what()+strlen(e.what())-strlen(str));
}

TEST (IOException)
{
    const char* str = "Francesca Lucchini";
    IOException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Francesca Lucchini", e.what()+strlen(e.what())-strlen(str));
}

TEST (NullPointException)
{
    const char* str = "Eila Ilmatar Juutilainen";
    NullPointerException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Eila Ilmatar Juutilainen", e.what()+strlen(e.what())-strlen(str));
}

TEST (SecurityException)
{
    const char* str = "Sanya V. Litvyak";
    SecurityException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Sanya V. Litvyak", e.what()+strlen(e.what())-strlen(str));
}

TEST (OpenGLException)
{
    const char* str = "Erica Hartmann";
    OpenGLException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Erica Hartmann", e.what()+strlen(e.what())-strlen(str));
}

TEST (NotImplementedException)
{
    const char* str = "Gertrud Barkhorn";
    NotImplementedException e(__FILE__, __func__, "%s", str);
    CHECK_EQUAL ("Gertrud Barkhorn", e.what()+strlen(e.what())-strlen(str));
}
