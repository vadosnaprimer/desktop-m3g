#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace std;
using namespace m3g;


extern "C" void Init_m3g();


void Init_m3g()
{
    // Declare 30 classes of M3G defined in JSR184
    VALUE rb_mM3G                 = rb_define_module ("M3G");
    VALUE rb_cGraphics3D          = rb_define_class_under (rb_mM3G, "Graphics3D",          rb_cObject);
    VALUE rb_cLoader              = rb_define_class_under (rb_mM3G, "Loader",              rb_cObject);
    VALUE rb_cObject3D            = rb_define_class_under (rb_mM3G, "Object3D",            rb_cObject);
    VALUE rb_cAnimationController = rb_define_class_under (rb_mM3G, "AnimationController", rb_cObject3D);
    VALUE rb_cAnimationTrack      = rb_define_class_under (rb_mM3G, "AnimationTrack",      rb_cObject3D);
    VALUE rb_cAppearance          = rb_define_class_under (rb_mM3G, "Appearance",          rb_cObject3D);
    VALUE rb_cBackground          = rb_define_class_under (rb_mM3G, "Background",          rb_cObject3D);
    VALUE rb_cCompositingMode     = rb_define_class_under (rb_mM3G, "CompositingMode",     rb_cObject3D);
    VALUE rb_cFog                 = rb_define_class_under (rb_mM3G, "Fog",                 rb_cObject3D);
    VALUE rb_cImage2D             = rb_define_class_under (rb_mM3G, "Image2D",             rb_cObject3D);
    VALUE rb_cIndexBuffer         = rb_define_class_under (rb_mM3G, "IndexBuffer",         rb_cObject3D);
    VALUE rb_cTriangleStripArray  = rb_define_class_under (rb_mM3G, "TriangleStripArray",  rb_cIndexBuffer);
    VALUE rb_cKeyframeSequence    = rb_define_class_under (rb_mM3G, "KeyframeSequence",    rb_cObject3D);
    VALUE rb_cMaterial            = rb_define_class_under (rb_mM3G, "Material",            rb_cObject3D);
    VALUE rb_cPolygonMode         = rb_define_class_under (rb_mM3G, "PolygonMode",         rb_cObject3D);
    VALUE rb_cTransformable       = rb_define_class_under (rb_mM3G, "Transformable",       rb_cObject3D);
    VALUE rb_cNode                = rb_define_class_under (rb_mM3G, "Node",                rb_cTransformable);
    VALUE rb_cCamera              = rb_define_class_under (rb_mM3G, "Camera",              rb_cNode);
    VALUE rb_cGroup               = rb_define_class_under (rb_mM3G, "Group",               rb_cNode);
    VALUE rb_cWorld               = rb_define_class_under (rb_mM3G, "World",               rb_cGroup);
    VALUE rb_cLight               = rb_define_class_under (rb_mM3G, "Light",               rb_cNode);
    VALUE rb_cMesh                = rb_define_class_under (rb_mM3G, "Mesh",                rb_cNode);
    VALUE rb_cMorphingMesh        = rb_define_class_under (rb_mM3G, "MorphingMesh",        rb_cMesh);
    VALUE rb_cSkinnedMesh         = rb_define_class_under (rb_mM3G, "SkinnedMesh",         rb_cMesh);
    VALUE rb_cSprite3D            = rb_define_class_under (rb_mM3G, "Sprite3D",            rb_cNode);
    VALUE rb_cTexture2D           = rb_define_class_under (rb_mM3G, "Texture2D",           rb_cTransformable);
    VALUE rb_cVertexArray         = rb_define_class_under (rb_mM3G, "VertexArray",         rb_cObject3D);
    VALUE rb_cVertexBuffer        = rb_define_class_under (rb_mM3G, "VertexBuffer",        rb_cObject3D);
    VALUE rb_cRayIntersection     = rb_define_class_under (rb_mM3G, "RayIntersection",     rb_cObject);
    VALUE rb_cTransform           = rb_define_class_under (rb_mM3G, "Transform",           rb_cObject);

    // inner struct for easy use
    VALUE rb_cActiveInterval = rb_define_class ("ActiveInterval", rb_cObject);
    VALUE rb_cCrop           = rb_define_class ("Crop", rb_cObject);
    VALUE rb_cImageMode      = rb_define_class ("ImageMode", rb_cObject);
    VALUE rb_cProjection     = rb_define_class ("Projection", rb_cObject);
    VALUE rb_cTextureCoord2D = rb_define_class ("TextureCoord2D", rb_cObject);
    VALUE rb_cViewport       = rb_define_class ("Viewport", rb_cObject);

    // register all methods in 30 classes
    register_Graphics3D (rb_cGraphics3D);
    register_Loader (rb_cLoader);
    register_AnimationController (rb_cAnimationController);
    register_AnimationTrack (rb_cAnimationTrack);
    register_Appearance (rb_cAppearance);
    register_Background (rb_cBackground);
    register_CompositingMode (rb_cCompositingMode);
    register_Fog (rb_cFog);
    register_Group (rb_cGroup);
    register_Image2D (rb_cImage2D);
    register_IndexBuffer (rb_cIndexBuffer);
    register_TriangleStripArray (rb_cTriangleStripArray);
    register_KeyframeSequence (rb_cKeyframeSequence);
    register_Material (rb_cMaterial);
    register_PolygonMode (rb_cPolygonMode);
    register_Transformable (rb_cTransformable);
    register_Node (rb_cNode);
    register_Camera (rb_cCamera);
    register_Group (rb_cGroup);
    register_World (rb_cWorld);
    register_Light (rb_cLight);
    register_Mesh (rb_cMesh);
    register_MorphingMesh (rb_cMorphingMesh);
    register_SkinnedMesh (rb_cSkinnedMesh);
    register_Sprite3D (rb_cSprite3D);
    register_Texture2D (rb_cTexture2D);
    register_VertexArray (rb_cVertexArray);
    register_VertexBuffer (rb_cVertexBuffer);
    register_RayIntersection (rb_cRayIntersection);
    register_Transform (rb_cTransform);


    // register inner struct
    register_ActiveInterval (rb_cActiveInterval);
    register_Crop (rb_cCrop);
    register_ImageMode (rb_cImageMode);
    register_Projection (rb_cProjection);
    register_TextureCoord2D (rb_cTextureCoord2D);
    register_Viewport (rb_cViewport);

}

