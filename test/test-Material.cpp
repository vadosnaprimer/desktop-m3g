#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Material.hpp"
using namespace std;
using namespace m3g;

TEST (Material_default_variables)
{
  Material* mat = new Material;

  CHECK_EQUAL (OBJTYPE_MATERIAL, mat->getObjectType());
  CHECK_EQUAL (false, mat->isVertexColorTrackingEnabled());
  CHECK_EQUAL (0x00333333, mat->getColor(Material::AMBIENT));
  CHECK_EQUAL (0xffcccccc, mat->getColor(Material::DIFFUSE));
  CHECK_EQUAL (0x00000000, mat->getColor(Material::EMISSIVE));
  CHECK_EQUAL (0x00000000, mat->getColor(Material::SPECULAR));
  CHECK_EQUAL (0.0, mat->getShininess());

  delete mat;
}

TEST (Material_set_variables)
{
  Material* mat = new Material;

  mat->setColor (Material::AMBIENT,  0x12345678);
  mat->setColor (Material::DIFFUSE,  0x23456789);
  mat->setColor (Material::EMISSIVE, 0x3456789a);
  mat->setColor (Material::SPECULAR, 0x456789ab);
  mat->setShininess (1.0);
  mat->setVertexColorTrackingEnable (true);

  cout << hex;
  CHECK_EQUAL (true, mat->isVertexColorTrackingEnabled());
  CHECK_EQUAL (0x00345678, mat->getColor(Material::AMBIENT));
  CHECK_EQUAL (0x23456789, mat->getColor(Material::DIFFUSE));
  CHECK_EQUAL (0x0056789a, mat->getColor(Material::EMISSIVE));
  CHECK_EQUAL (0x006789ab, mat->getColor(Material::SPECULAR));
  CHECK_EQUAL (1.0, mat->getShininess());
  cout << dec;

  delete mat;
}
