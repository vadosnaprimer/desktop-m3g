#include <strstream>
#include <iostream>
#include "../Light.hpp"
#include "parse-Node.hpp"
using namespace std;
using namespace m3g;
#include <cstdlib>

void parse_Light (istrstream& iss, vector<Object3D*>& objs)
{
  Light* lig = new Light;

  parse_Node (iss, objs, lig);

  float attenuation_constant;
  float attenuation_linear;
  float attenuation_quadratic;
  iss.read ((char*)&attenuation_constant, 4);
  iss.read ((char*)&attenuation_linear, 4);
  iss.read ((char*)&attenuation_quadratic, 4);

  /*
    // BlenderのM3Gエクスポーターが変な値を出力してくるので
    // 減衰定数は設定しない。エクスポーターが直ったら復活させる。
  lig->setAttenuation (attenuation_constant, attenuation_linear, attenuation_quadratic);
  cout << "attenuation_constant  = "  << attenuation_constant << "\n";
  cout << "attenuation_quadratic = " << attenuation_quadratic << "\n";
  cout << "attenuation_linear    = " << attenuation_linear << "\n";
  */

  unsigned int color = 0;
  iss.read ((char*)&color, 3);
  lig->setColor (color);

  unsigned char mode;
  iss.read ((char*)&mode, 1);
  lig->setMode (mode);

  float intensity;
  iss.read ((char*)&intensity, 4);
  lig->setIntensity (intensity);

  float spot_angle;
  iss.read ((char*)&spot_angle, 4);
  lig->setSpotAngle (spot_angle);

  float spot_exponent;
  iss.read ((char*)&spot_exponent, 4);
  lig->setSpotExponent (spot_exponent);

  /*
  lig->print (cout);
  lig->Node::print (cout);
  lig->Object3D::print (cout);
  */

  objs.push_back (lig);

}
