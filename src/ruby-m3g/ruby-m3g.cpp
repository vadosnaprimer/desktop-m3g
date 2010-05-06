#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace std;
using namespace m3g;


extern "C" void Init_m3g();

VALUE rb_mM3G;
VALUE rb_cGraphics3D;
VALUE rb_cLoader;
VALUE rb_cObject3D;
VALUE rb_cAnimationController;
VALUE rb_cAnimationTrack;
VALUE rb_cAppearance;
VALUE rb_cTextures;
VALUE rb_cBackground;
VALUE rb_cCompositingMode;
VALUE rb_cFog;
VALUE rb_cImage2D;
VALUE rb_cIndexBuffer;
VALUE rb_cTriangleStripArray;
VALUE rb_cKeyframeSequence;
VALUE rb_cMaterial;
VALUE rb_cPolygonMode;
VALUE rb_cTransformable;
VALUE rb_cNode;
VALUE rb_cCamera;
VALUE rb_cGroup;
VALUE rb_cWorld;
VALUE rb_cLight;
VALUE rb_cMesh;
VALUE rb_cMorphingMesh;
VALUE rb_cSkinnedMesh;
VALUE rb_cSprite3D;
VALUE rb_cTexture2D;
VALUE rb_cVertexArray;
VALUE rb_cVertexBuffer;
VALUE rb_cRayIntersection;
VALUE rb_cTransform;

void Init_m3g()
{
    // Declare 30 classes of M3G defined in JSR184
    rb_mM3G                 = rb_define_module ("M3G");
    rb_cGraphics3D          = rb_define_class_under (rb_mM3G, "Graphics3D",          rb_cObject);
    rb_cLoader              = rb_define_class_under (rb_mM3G, "Loader",              rb_cObject);
    rb_cObject3D            = rb_define_class_under (rb_mM3G, "Object3D",            rb_cObject);
    rb_cAnimationController = rb_define_class_under (rb_mM3G, "AnimationController", rb_cObject3D);
    rb_cAnimationTrack      = rb_define_class_under (rb_mM3G, "AnimationTrack",      rb_cObject3D);
    rb_cAppearance          = rb_define_class_under (rb_mM3G, "Appearance",          rb_cObject3D);
    rb_cBackground          = rb_define_class_under (rb_mM3G, "Background",          rb_cObject3D);
    rb_cCompositingMode     = rb_define_class_under (rb_mM3G, "CompositingMode",     rb_cObject3D);
    rb_cFog                 = rb_define_class_under (rb_mM3G, "Fog",                 rb_cObject3D);
    rb_cImage2D             = rb_define_class_under (rb_mM3G, "Image2D",             rb_cObject3D);
    rb_cIndexBuffer         = rb_define_class_under (rb_mM3G, "IndexBuffer",         rb_cObject3D);
    rb_cTriangleStripArray  = rb_define_class_under (rb_mM3G, "TriangleStripArray",  rb_cIndexBuffer);
    rb_cKeyframeSequence    = rb_define_class_under (rb_mM3G, "KeyframeSequence",    rb_cObject3D);
    rb_cMaterial            = rb_define_class_under (rb_mM3G, "Material",            rb_cObject3D);
    rb_cPolygonMode         = rb_define_class_under (rb_mM3G, "PolygonMode",         rb_cObject3D);
    rb_cTransformable       = rb_define_class_under (rb_mM3G, "Transformable",       rb_cObject3D);
    rb_cNode                = rb_define_class_under (rb_mM3G, "Node",                rb_cTransformable);
    rb_cCamera              = rb_define_class_under (rb_mM3G, "Camera",              rb_cNode);
    rb_cGroup               = rb_define_class_under (rb_mM3G, "Group",               rb_cNode);
    rb_cWorld               = rb_define_class_under (rb_mM3G, "World",               rb_cGroup);
    rb_cLight               = rb_define_class_under (rb_mM3G, "Light",               rb_cNode);
    rb_cMesh                = rb_define_class_under (rb_mM3G, "Mesh",                rb_cNode);
    rb_cMorphingMesh        = rb_define_class_under (rb_mM3G, "MorphingMesh",        rb_cMesh);
    rb_cSkinnedMesh         = rb_define_class_under (rb_mM3G, "SkinnedMesh",         rb_cMesh);
    rb_cSprite3D            = rb_define_class_under (rb_mM3G, "Sprite3D",            rb_cNode);
    rb_cTexture2D           = rb_define_class_under (rb_mM3G, "Texture2D",           rb_cTransformable);
    rb_cVertexArray         = rb_define_class_under (rb_mM3G, "VertexArray",         rb_cObject3D);
    rb_cVertexBuffer        = rb_define_class_under (rb_mM3G, "VertexBuffer",        rb_cObject3D);
    rb_cRayIntersection     = rb_define_class_under (rb_mM3G, "RayIntersection",     rb_cObject);
    rb_cTransform           = rb_define_class_under (rb_mM3G, "Transform",           rb_cObject);

    

    // register all methods in 30 classes
    register_Graphics3D ();
    register_Loader ();
    register_AnimationController ();
    register_AnimationTrack ();
    register_Appearance ();
    register_Background ();
    register_CompositingMode ();
    register_Fog ();
    register_Group ();
    register_Image2D ();
    register_IndexBuffer ();
    register_TriangleStripArray ();
    register_KeyframeSequence ();
    register_Material ();
    register_PolygonMode ();
    register_Transformable ();
    register_Node ();
    register_Camera ();
    register_Group ();
    register_World ();
    register_Light ();
    register_Mesh ();
    register_MorphingMesh ();
    register_SkinnedMesh ();
    register_Sprite3D ();
    register_Texture2D ();
    register_VertexArray ();
    register_VertexBuffer ();
    register_RayIntersection ();
    register_Transform ();


}

