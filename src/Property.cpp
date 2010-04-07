#include "Property.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace m3g;
using namespace std;


Property:: Property (const char* name, int value) :
  property_name(name), property_value(value)
{
  if (name == NULL) {
    throw NullPointException (__FILE__, __func__, "Name is NULL.");
  }
}


Property:: ~Property ()
{
}

const char* Property:: name () const
{
  return property_name;
}


int Property:: value () const
{
  return property_value;
}

std::ostream& Property:: print (std::ostream& out) const
{
  out << property_name << " --> " << property_value;
  return out;
}

std::ostream& operator<< (std::ostream& out, const m3g::Property& prop)
{
  return prop.print (out);
}
