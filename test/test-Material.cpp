#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Material.hpp"
using namespace std;
using namespace m3g;

TEST (Material_default_variables)
{
  Material* mat = new Material;

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

  CHECK_EQUAL (true, mat->isVertexColorTrackingEnabled());
  CHECK_EQUAL (0x00345678, mat->getColor(Material::AMBIENT));
  CHECK_EQUAL (0x23456789, mat->getColor(Material::DIFFUSE));
  CHECK_EQUAL (0x0056789a, mat->getColor(Material::EMISSIVE));
  CHECK_EQUAL (0x006789ab, mat->getColor(Material::SPECULAR));
  CHECK_EQUAL (1.0, mat->getShininess());

  delete mat;
}

TEST (Material_duplicate)
{
  Material* mat0 = new Material;

  mat0->setColor (Material::AMBIENT,  0x12345678);
  mat0->setColor (Material::DIFFUSE,  0x23456789);
  mat0->setColor (Material::EMISSIVE, 0x3456789a);
  mat0->setColor (Material::SPECULAR, 0x456789ab);
  mat0->setShininess (1.0);
  mat0->setVertexColorTrackingEnable (true);

  Material* mat1 = mat0->duplicate();

  CHECK_EQUAL (mat0->isVertexColorTrackingEnabled(), mat1->isVertexColorTrackingEnabled());
  CHECK_EQUAL (mat0->getColor(Material::AMBIENT)   , mat1->getColor(Material::AMBIENT));
  CHECK_EQUAL (mat0->getColor(Material::DIFFUSE)   , mat1->getColor(Material::DIFFUSE));
  CHECK_EQUAL (mat0->getColor(Material::EMISSIVE)  , mat1->getColor(Material::EMISSIVE));
  CHECK_EQUAL (mat0->getColor(Material::SPECULAR)  , mat1->getColor(Material::SPECULAR));
  CHECK_EQUAL (mat0->getShininess()                , mat1->getShininess());

  delete mat0;
  delete mat1;
}
