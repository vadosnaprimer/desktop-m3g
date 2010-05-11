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

// M3Gの例外クラス
VALUE rb_eArithmeticException;
VALUE rb_eIllegalArgumentException;
VALUE rb_eIllegalStateException;
VALUE rb_eIndexOutOfBoundsException;
VALUE rb_eIOException;
VALUE rb_eNullPointerException;
VALUE rb_eSecurityException;
VALUE rb_eNotImplementedException;
VALUE rb_eOpenGLException;
VALUE rb_eInternalException;


void Init_m3g()
{
    cout << "Init_m3g: called\n";

    // Declare "M3G" module
    rb_mM3G = rb_define_module ("M3G");

    // Register all 30 classes of M3G
    register_Graphics3D ();
    register_Loader ();
    register_Object3D ();
    register_AnimationController ();
    register_AnimationTrack ();
    register_Appearance ();
    register_Background ();
    register_CompositingMode ();
    register_Fog ();
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

    // Register all Exception classes of M3G
    register_Exception ();
}

