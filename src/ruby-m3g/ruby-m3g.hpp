

#ifndef __RUBY_M3G_HPP__
#define __RUBY_M3G_HPP__

// 古いrubyだとこのマクロがないので
#ifndef RFLOAT_VALUE
#define RFLOAT_VALUE(v) (RFLOAT(v)->value)
#endif

#define NUMERIC2FLOAT(x)                     \
  (TYPE(x) == T_FLOAT ) ? RFLOAT_VALUE(x) :	\
  (TYPE(x) == T_BIGNUM) ? NUM2INT(x)      :	\
  (TYPE(x) == T_FIXNUM) ? FIX2INT(x)      :	\
  0;

// 最後0よりはこちらの方が良い
// rb_funcall(x, rb_intern("to_i"), 0)
// int id_to_i = rb_intern("to_i")

// M3Gで定義された30クラス
extern VALUE rb_mM3G;
extern VALUE rb_cGraphics3D;
extern VALUE rb_cLoader;
extern VALUE rb_cObject3D;
extern VALUE rb_cAnimationController;
extern VALUE rb_cAnimationTrack;
extern VALUE rb_cAppearance;
extern VALUE rb_cTextures;
extern VALUE rb_cBackground;
extern VALUE rb_cCompositingMode;
extern VALUE rb_cFog;
extern VALUE rb_cImage2D;
extern VALUE rb_cIndexBuffer;
extern VALUE rb_cTriangleStripArray;
extern VALUE rb_cKeyframeSequence;
extern VALUE rb_cMaterial;
extern VALUE rb_cPolygonMode;
extern VALUE rb_cTransformable;
extern VALUE rb_cNode;
extern VALUE rb_cCamera;
extern VALUE rb_cGroup;
extern VALUE rb_cWorld;
extern VALUE rb_cLight;
extern VALUE rb_cMesh;
extern VALUE rb_cMorphingMesh;
extern VALUE rb_cSkinnedMesh;
extern VALUE rb_cSprite3D;
extern VALUE rb_cTexture2D;
extern VALUE rb_cVertexArray;
extern VALUE rb_cVertexBuffer;
extern VALUE rb_cRayIntersection;
extern VALUE rb_cTransform;



void register_Graphics3D ();
void register_Loader ();
void register_Object3D ();
void register_AnimationController ();
void register_AnimationTrack ();
void register_Appearance ();
void register_Background ();
void register_CompositingMode ();
void register_Fog ();
void register_Group ();
void register_Image2D ();
void register_IndexBuffer ();
void register_TriangleStripArray ();
void register_KeyframeSequence ();
void register_Material ();
void register_PolygonMode ();
void register_Transformable ();
void register_Node ();
void register_Camera ();
void register_Group ();
void register_World ();
void register_Light ();
void register_Mesh ();
void register_MorphingMesh ();
void register_SkinnedMesh ();
void register_Sprite3D ();
void register_Texture2D ();
void register_VertexArray ();
void register_VertexBuffer ();
void register_RayIntersection ();
void register_Transform ();


#endif
