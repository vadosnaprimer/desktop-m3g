#include "RayIntersection.hpp"
#include <iostream>
#include "Node.hpp"
using namespace std;
using namespace m3g;

RayIntersection:: RayIntersection ()
{
}

RayIntersection:: ~RayIntersection ()
{
}

float RayIntersection:: getDistance () const
{
    return 0;
}

Node* RayIntersection:: getIntersected () const
{
    return 0;
}

float RayIntersection:: getNormalX () const
{
    return 0;
}

float RayIntersection:: getNormalY () const
{
    return 0;
}

float RayIntersection:: getNormalZ () const
{
    return 0;
}

void RayIntersection:: getRay (float* ray) const
{
}

int RayIntersection:: getSubmeshIndex () const
{
    return 0;
}

float RayIntersection:: getTextureS (int index) const
{
    return 0;
}

float RayIntersection:: getTextureT (int index) const
{
    return 0;
}

std::ostream& operator<< (std::ostream& out, const RayIntersection& ri)
{
    return out;
}


