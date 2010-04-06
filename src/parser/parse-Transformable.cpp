#include <strstream>
#include <iostream>
#include "parse-Object3D.hpp"
#include "parse-Transformable.hpp"
#include "../Transformable.hpp"
#include "../Exception.hpp"
using namespace std;
using namespace m3g;

void parse_Transformable (istrstream& iss, vector<Object3D*>& objs, Transformable* trans)
{
  if (trans == NULL) {
    throw NullPointException (__FILE__, __func__, "Transformabls is NULL.");
  }

  parse_Object3D (iss, objs, trans);

  bool has_comonent_transform;
  iss.read ((char*)&has_comonent_transform, 1);
  //cout << "has_comonent_transform = " << has_comonent_transform << "\n";
  if (has_comonent_transform) {
    float tx, ty, tz;
    iss.read ((char*)&tx, 4);
    iss.read ((char*)&ty, 4);
    iss.read ((char*)&tz, 4);
    trans->setTranslation (tx, ty, tz);

    float sx, sy, sz;
    iss.read ((char*)&sx, 4);
    iss.read ((char*)&sy, 4);
    iss.read ((char*)&sz, 4);
    trans->setScale (sx, sy, sz);

    float angle, ax, ay, az;
    iss.read ((char*)&angle, 4);
    iss.read ((char*)&ax, 4);
    iss.read ((char*)&ay, 4);
    iss.read ((char*)&az, 4);
    trans->setOrientation (angle, ax, ay, az);
  }

  bool has_general_transform;
  iss.read ((char*)&has_general_transform, 1);
  //cout << "has_general_transform = " << has_general_transform << "\n";
  if (has_general_transform) {
    float matrix[16];
    iss.read ((char*)matrix, 64);
    Transform tra;
    tra.set (matrix);
    trans->setTransform (tra);
  }

}
