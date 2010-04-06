#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Property.hpp"
using namespace std;
using namespace m3g;


TEST (Property_default_variables)
{
  Property* prop = new Property ("Joint Strike Wing", 501);

  CHECK_EQUAL ("Joint Strike Wing", prop->name());
  CHECK_EQUAL (501, prop->value());
}
