

#include "m3g.hpp"

#ifndef __RUBY_M3G_HPP__
#define __RUBY_M3G_HPP__


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

// M3Gの例外クラス
extern VALUE rb_eArithmeticException;
extern VALUE rb_eIllegalArgumentException;
extern VALUE rb_eIllegalStateException;
extern VALUE rb_eIndexOutOfBoundsException;
extern VALUE rb_eIOException;
extern VALUE rb_eNullPointerException;
extern VALUE rb_eSecurityException;
extern VALUE rb_eNotImplementedException;
extern VALUE rb_eOpenGLException;
extern VALUE rb_eInternalException;


// 30クラスの登録
extern void register_Graphics3D ();
extern void register_Loader ();
extern void register_Object3D ();
extern void register_AnimationController ();
extern void register_AnimationTrack ();
extern void register_Appearance ();
extern void register_Background ();
extern void register_CompositingMode ();
extern void register_Fog ();
extern void register_Group ();
extern void register_Image2D ();
extern void register_IndexBuffer ();
extern void register_TriangleStripArray ();
extern void register_KeyframeSequence ();
extern void register_Material ();
extern void register_PolygonMode ();
extern void register_Transformable ();
extern void register_Node ();
extern void register_Camera ();
extern void register_Group ();
extern void register_World ();
extern void register_Light ();
extern void register_Mesh ();
extern void register_MorphingMesh ();
extern void register_SkinnedMesh ();
extern void register_Sprite3D ();
extern void register_Texture2D ();
extern void register_VertexArray ();
extern void register_VertexBuffer ();
extern void register_RayIntersection ();
extern void register_Transform ();


// 例外クラスの登録
extern void register_Exception ();


#define __TRY__ try { 
#define __CATCH__  }                                                    \
    catch (const m3g::ArithmeticException&       e) { rb_raise (rb_eArithmeticException,       e.what()); } \
    catch (const m3g::IllegalArgumentException&  e) { rb_raise (rb_eIllegalArgumentException,  e.what()); } \
    catch (const m3g::IllegalStateException&     e) { rb_raise (rb_eIllegalStateException,     e.what()); } \
    catch (const m3g::IndexOutOfBoundsException& e) { rb_raise (rb_eIndexOutOfBoundsException, e.what()); } \
    catch (const m3g::IOException&               e) { rb_raise (rb_eIOException,               e.what()); } \
    catch (const m3g::NullPointerException&      e) { rb_raise (rb_eNullPointerException,      e.what()); } \
    catch (const m3g::SecurityException&         e) { rb_raise (rb_eSecurityException,         e.what()); } \
    catch (const m3g::NotImplementedException&   e) { rb_raise (rb_eNotImplementedException,   e.what()); } \
    catch (const m3g::OpenGLException&           e) { rb_raise (rb_eOpenGLException,           e.what()); } \
    catch (const m3g::InternalException&         e) { rb_raise (rb_eInternalException,         e.what()); } \
    catch (const std::bad_alloc&                 e) { rb_raise (rb_eNoMemError,                e.what()); } \
    catch (const std::exception&                 e) { rb_raise (rb_eRuntimeError,              e.what()); } \
    catch (...)                                     { rb_raise (rb_eStandardError, "Undetermined generic error."); }

#endif
