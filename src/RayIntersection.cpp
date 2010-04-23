#include "RayIntersection.hpp"
#include "Exception.hpp"
#include <iostream>
#include "Node.hpp"
using namespace std;
using namespace m3g;

RayIntersection:: RayIntersection ()
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
}

RayIntersection:: ~RayIntersection ()
{
}

float RayIntersection:: getDistance () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

Node* RayIntersection:: getIntersected () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

float RayIntersection:: getNormalX () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

float RayIntersection:: getNormalY () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

float RayIntersection:: getNormalZ () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

void RayIntersection:: getRay (float* ray) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
}

int RayIntersection:: getSubmeshIndex () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

float RayIntersection:: getTextureS (int index) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

float RayIntersection:: getTextureT (int index) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, not implemented yet.");
  return 0;
}

std::ostream& RayIntersection:: print (std::ostream& out) const
{
  out << "RayIntersection: \n";
  return out;
}

std::ostream& operator<< (std::ostream& out, const RayIntersection& ri)
{
  return ri.print (out);
}


