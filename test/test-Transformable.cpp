#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstdlib>
#include "Transformable.hpp"
using namespace std;
using namespace m3g;


TEST (Transformable_set_variables)
{
  Transformable trans;

  CHECK_EQUAL (OBJTYPE_TRANSFORMABLE, trans.getObjectType());

  trans.setOrientation (90, 1,0,0);
  trans.setScale (1,2,3);
  trans.setTranslation (-1,0,1);

  Transform tra0;
  tra0.postRotate (90, 1,0,0);
  tra0.postScale  (1,2,3);
  tra0.postTranslate (-1,0,1);
  trans.setTransform (tra0);


  float a[4];
  trans.getOrientation (a);
  CHECK_CLOSE (90.f, a[0], 0.00001);
  CHECK_CLOSE (1.f, a[1], 0.00001);
  CHECK_CLOSE (0.f, a[2], 0.00001);
  CHECK_CLOSE (0.f, a[3], 0.00001);

  float s[3];
  trans.getScale (s);
  CHECK_CLOSE (1.f, s[0], 0.00001);
  CHECK_CLOSE (2.f, s[1], 0.00001);
  CHECK_CLOSE (3.f, s[2], 0.00001);

  float t[3];
  trans.getTranslation (t);
  CHECK_CLOSE (-1.f, t[0], 0.00001);
  CHECK_CLOSE (0.f, t[1], 0.00001);
  CHECK_CLOSE (1.f, t[2], 0.00001);
  
  Transform tra1;
  float f0[16];
  float f1[16];
  trans.getTransform (&tra1);
  tra0.get (f0);
  tra1.get (f1);
  CHECK_CLOSE (f0[0], f1[0], 0.00001);
  CHECK_CLOSE (f0[5], f1[5], 0.00001);
  CHECK_CLOSE (f0[14], f1[14], 0.00001);

}


TEST (Transformable_append_variables)
{
  Transformable trans;

  trans.scale (1,2,3);
  trans.scale (1,2,3);
  trans.postRotate (60, 1,0,0);
  trans.preRotate (-60, 1,0,0);
  trans.translate (1,2,3);
  trans.translate (1,2,3);

  Transform tra;
  trans.getCompositeTransform (&tra);
  float m[4][4];
  tra.get ((float*)m);

  // scale
  CHECK_CLOSE (1.f, m[0][0], 0.00001);
  CHECK_CLOSE (4.f, m[1][1], 0.00001);
  CHECK_CLOSE (9.f, m[2][2], 0.00001);

  // translate
  CHECK_CLOSE (2.f, m[0][3], 0.00001);
  CHECK_CLOSE (4.f, m[1][3], 0.00001);
  CHECK_CLOSE (6.f, m[2][3], 0.00001);

  // rotation
  CHECK_CLOSE (0.f, m[0][1], 0.00001);
  CHECK_CLOSE (0.f, m[1][0], 0.00001);
  CHECK_CLOSE (0.f, m[1][2], 0.00001);
  CHECK_CLOSE (0.f, m[2][1], 0.00001);

  // 目視で確認した方が早い
  // for (int i = 0; i < 16; i++) {
  //  cout << m[i] << " ";
  // }
  // cout << "\n";


}
