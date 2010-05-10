#include "MorphingMesh.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Appearance.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;
using namespace m3g;
    
MorphingMesh:: MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets,
                             int num_submesh, IndexBuffer** submeshes, Appearance** appearances) :
  Mesh (base, num_submesh, submeshes, appearances), morphed_vertices(0)
{
  if (num_target < 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of target is invalid, num=%d.", num_target);
  }
  if (targets == NULL) {
    throw NullPointException (__FILE__, __func__, "Morph targets are NULL.");
  }
  for (int i = 0; i < num_target; i++) {
    if (targets[i] == NULL) {
      throw NullPointException (__FILE__, __func__, " Target vertices is NULL, index=%d.", i);
    }
  }
  if (base->getPositions(0) == NULL) {
    throw NullPointException (__FILE__, __func__, "Base vertices has no positions.");
  }

   morphed_vertices = base->duplicate ();
  
   // 注意：モーフィング変形後のpositions,normals,colorsを保存するために新しくnewし直す。
   // VertexBufferをduplicate()しただけでは同じインスタンスを指している。

   float        scale_bias[4];
   VertexArray* base_positions = base->getPositions (scale_bias);
   if (base_positions) {
     VertexArray* morphed_positions = base_positions->duplicate();
     morphed_vertices->setPositions (morphed_positions, scale_bias[0], &scale_bias[1]);
   }
   
   VertexArray* base_normals = base->getNormals ();
   if (base_normals) {
     VertexArray* morphed_normals = base_normals->duplicate ();
     morphed_vertices->setNormals (morphed_normals);
   }

   VertexArray* base_colors = base->getColors ();
   if (base_colors) {
     VertexArray* morphed_colors = base_colors->duplicate ();
     morphed_vertices->setColors (morphed_colors);
   }


  morph_targets.reserve (num_target);
  for (int i = 0; i < num_target; i++) {
    VertexBuffer* vbuf = *targets++;
    morph_targets.push_back (vbuf);
  }
  

  morph_weights.reserve (num_target);
  for (int i = 0; i < num_target; i++) {
    morph_weights.push_back (0);
  }
}

MorphingMesh:: MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets, IndexBuffer* submesh, Appearance* appearance) :
    Mesh (base, submesh, appearance)
{
  *this = MorphingMesh (base, num_target, targets, 1, &submesh, &appearance);
}

MorphingMesh:: ~MorphingMesh ()
{
}

MorphingMesh* MorphingMesh:: duplicate () const
{
  MorphingMesh* morphing_mesh = new MorphingMesh (*this);
  Mesh* mesh = Mesh::duplicate();
  *(Mesh*)morphing_mesh = *mesh;
  delete mesh;
  return morphing_mesh;
}


void MorphingMesh:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation track is NULL.");
  }
  int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::ALPHA       &&
      property != AnimationTrack::PICKABILITY &&
      property != AnimationTrack::VISIBILITY  &&
      property != AnimationTrack::ORIENTATION &&
      property != AnimationTrack::SCALE       &&
      property != AnimationTrack::TRANSLATION &&
      property != AnimationTrack::MORPH_WEIGHTS) {
    throw IllegalArgumentException (__FILE__, __func__, "Animation target is invalid for this MorphMesh, property=%d.", property);
  }

  Object3D:: addAnimationTrack (animation_track);
}


int MorphingMesh:: animate (int world_time)
{
  Mesh:: animate (world_time);

  bool   is_weights_modefied = false;
  float* new_weights         = new float[morph_weights.size()];
  fill (new_weights, new_weights+morph_weights.size(), 0);

  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "Material: missing controller, this animation track is ignored.\n";
      continue;
    }
    if (!controller->isActiveInterval(world_time)) {
      continue;
    }
    float animation_weight = controller->getWeight ();
    float local_time       = controller->getPosition (world_time);

 
    switch (track->getTargetProperty()) {
    case AnimationTrack::MORPH_WEIGHTS: {
      // 注意：仕様では両者は必ずしも同じでなくて良い
      int    num   = max ((int)morph_weights.size(), keyframe->getComponentCount());
      float* value = new float[num];
      fill (value, value+num, 0);
      keyframe->getFrame (local_time, value);
      for (int i = 0; i < (int)morph_weights.size(); i++) {
	new_weights[i] += value[i] * animation_weight;
      }
      is_weights_modefied = true;
      delete [] value;
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class handle it.
    }
    }
  }

  if (is_weights_modefied) {
    //cout << "MorphingMesh: weights --> ";
    for (int i = 0; i < (int)morph_weights.size(); i++) {
      //cout << new_weights[i] << ", ";
      morph_weights[i] = new_weights[i];
    }
    //cout << "\n";
    updateMorphedVertices ();
  }

  //for (int i = 0; i < (int)morph_weights.size(); i++) {
  //  cout << "B: morph_weights[" << i << "] = " << morph_weights[i] << "\n";
  //}


  return 0;
}


void MorphingMesh:: updateMorphedVertices ()
{
  float              scale_bias[4];
  const VertexArray* base_positions    = vertices->getPositions (scale_bias);
  const VertexArray* base_normals      = vertices->getNormals ();
  const VertexArray* base_colors       = vertices->getColors ();
  vector<const VertexArray*> morph_target_positions;
  vector<const VertexArray*> morph_target_normals;
  vector<const VertexArray*> morph_target_colors;
  for (int i = 0; i < (int)morph_targets.size(); i++) {
    morph_target_positions.push_back (morph_targets[i]->getPositions(0));
    morph_target_normals.push_back (morph_targets[i]->getNormals());
    morph_target_colors.push_back (morph_targets[i]->getColors());
  }
  VertexArray* morphed_positions = morphed_vertices->getPositions (0);
  VertexArray* morphed_normals   = morphed_vertices->getNormals ();
  VertexArray* morphed_colors    = morphed_vertices->getColors ();

  // 位置
  if (base_positions) {
    morphed_positions->setMorphing (base_positions, morph_target_positions, morph_weights);
  }

  // 法線
  if (base_normals) {
    morphed_normals->setMorphing (base_normals, morph_target_normals, morph_weights);
  }

  // 頂点カラー
  if (base_colors) {
    morphed_colors->setMorphing (base_colors, morph_target_colors, morph_weights);
  }

  // デフォルトカラー
  if (1) {
    int base_color    = vertices->getDefaultColor ();
    int morphed_color = vertices->getDefaultColor ();
    for (int t = 0; t < (int)morph_targets.size(); t++) {
      int target_color = morph_targets[t]->getDefaultColor ();
      morphed_color += morph_weights[t] * (target_color - base_color);
    }
    morphed_color = clamp (0,1, morphed_color);
    morphed_vertices->setDefaultColor (morphed_color);
  }
  

}


VertexBuffer* MorphingMesh:: getMorphTarget (int index) const
{
  if (index < 0 || index >= (int)morph_targets.size()) {
    throw IndexOutOfBoundsException (__FILE__, __func__, "Target index is invalid. index=%d.", index);
  }
  return morph_targets[index];
}

int MorphingMesh:: getMorphTargetCount () const
{
  return morph_targets.size();
}

void MorphingMesh:: getWeights (float* weights) const
{
  if (weights == NULL) {
    throw NullPointException (__FILE__, __func__, "Weights is NULL.");
  }

  for (int i = 0; i < (int)morph_weights.size(); i++) {
    *weights++ = morph_weights[i];
  }
}

void MorphingMesh:: setWeights (int num_weights, float* weights)
{
  if (weights == NULL) {
    throw NullPointException (__FILE__, __func__, "Weights is NULL.");
  }
  if (num_weights != (int)morph_weights.size()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of weights is invalid, %d <--> %d.", num_weights, morph_weights.size());
  }

  for (int i = 0; i < (int)morph_weights.size(); i++) {
    morph_weights[i] = *weights++;
    //cout << "weights = " << morph_weights[i] << "\n";
  }

  updateMorphedVertices ();
}

void MorphingMesh:: render (RenderState& state) const
{
  // Mesh::render()でチェックするのでここでは何もしなくて良い

  //cout << "MorphingMesh: render\n";

  // 注意：vertices が morphed_vertices に変わった事を除けば Mesh::render()と同一。
  // M3Gの仕様で vertices を書き換える事は禁止されているので元に戻す。

  VertexBuffer* tmp = vertices;
  (const_cast<MorphingMesh*>(this))->vertices = morphed_vertices;

  Mesh::render (state);

  (const_cast<MorphingMesh*>(this))->vertices = tmp;

}

std::ostream& MorphingMesh:: print (std::ostream& out) const
{
  out << "MorhpingMesh: ";
  out << "  morph_target_count=" << morph_targets.size();
  out << ", weights=[";
  for (int i = 0; i < (int)morph_weights.size(); i++) {
    out << morph_weights[i] << ",";
  }
  out << "]";
  return out;
}

std::ostream& operator<< (std::ostream& out, const MorphingMesh& mesh)
{
  return mesh.print (out);
}



