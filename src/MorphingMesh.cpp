#include "MorphingMesh.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Appearance.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;
using namespace m3g;
    
MorphingMesh:: MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets, int num_submesh, IndexBuffer** submeshes, int num_appearance, Appearance** appearances) :
    Mesh (base, num_submesh, submeshes, num_appearance, appearances)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, MrphingMesh is not implemented.");
}

MorphingMesh:: MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets, IndexBuffer* submeshes, Appearance* appearances) :
    Mesh (base, submeshes, appearances)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, MrphingMesh is not implemented.");
}

MorphingMesh:: ~MorphingMesh ()
{
}

MorphingMesh* MorphingMesh:: duplicate () const
{
  return new MorphingMesh (*this);
}



void MorphingMesh:: addAnimationTrack (AnimationTrack* animation_track)
{
}

int MorphingMesh:: animate (int world_time)
{
  return 0;
}

VertexBuffer* MorphingMesh:: getMorphTarget (int index) const
{
    return 0;
}

int MorphingMesh:: getMorphTargetCount () const
{
    return 0;
}

void MorphingMesh:: getWeights (float* wights) const
{
}

void MorphingMesh:: setWeights (float* wights)
{
}

void MorphingMesh:: render (RenderState& state) const
{
}

std::ostream& MorphingMesh:: print (std::ostream& out) const
{
  out << "MorhpingMesh: \n";
  return out;
}

std::ostream& operator<< (std::ostream& out, const MorphingMesh& m)
{
    return out;
}



