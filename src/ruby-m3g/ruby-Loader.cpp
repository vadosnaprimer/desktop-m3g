#include <iostream>
#include <typeinfo>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

extern VALUE ruby_Object3D_free            (Object3D* ptr);
extern VALUE ruby_AnimationController_free (AnimationController* ptr);
extern VALUE ruby_AnimationTrack_free      (AnimationTrack* ptr);
extern VALUE ruby_Appearance_free          (Appearance* ptr);
extern VALUE ruby_Background_free          (Background* ptr);
extern VALUE ruby_CompositingMode_free     (CompositingMode* ptr);
extern VALUE ruby_Fog_free                 (Fog* ptr);
extern VALUE ruby_Image2D_free             (Image2D* ptr);
extern VALUE ruby_TriangleStripArray_free  (TriangleStripArray* ptr);
extern VALUE ruby_KeyframeSequence_free    (KeyframeSequence* ptr);
extern VALUE ruby_Material_free            (Material* ptr);
extern VALUE ruby_PolygonMode_free         (PolygonMode* ptr);
extern VALUE ruby_Camera_free              (Camera* ptr);
extern VALUE ruby_Group_free               (Group* ptr);
extern VALUE ruby_World_free               (World* ptr);
extern VALUE ruby_Light_free               (Light* ptr);
extern VALUE ruby_Mesh_free                (Mesh* ptr);
extern VALUE ruby_MorphingMesh_free        (MorphingMesh* ptr);
extern VALUE ruby_SkinnedMesh_free         (SkinnedMesh* ptr);
extern VALUE ruby_Sprite3D_free            (Sprite3D* ptr);
extern VALUE ruby_Texture2D_free           (Texture2D* ptr);
extern VALUE ruby_VertexArray_free         (VertexArray* ptr);
extern VALUE ruby_VertexBuffer_free        (VertexBuffer* ptr);




VALUE ruby_Loader_load (int argc, VALUE* argv, VALUE self)
{
  std::vector<Object3D*> objs;

  VALUE val_arg1, val_arg2, val_arg3;

  int num = rb_scan_args (argc, argv, "12", &val_arg1, &val_arg2, &val_arg3);
    switch (num) {
    case 1: {
      const char* name = STR2CSTR (val_arg1);
      objs =  Loader::load (name);
      break;
    }
    case 3: {
      int         length = NUM2INT  (val_arg1);
      const char* data   = STR2CSTR (val_arg2);
      int         offset = NUM2INT  (val_arg3);
      objs = Loader::load (length, data, offset);
      break;
    }
    default: {
      // えらー
    }
    }

    VALUE val_objs = rb_ary_new ();
    for (int i = 0; i < (int)objs.size(); i++) {
      VALUE val_obj;
      if      (typeid(*objs[i]) == typeid(AnimationController)) val_obj = Data_Wrap_Struct(rb_cAnimationController, 0, ruby_AnimationController_free, objs[i]);
      else if (typeid(*objs[i]) == typeid(AnimationTrack))      val_obj = Data_Wrap_Struct(rb_cAnimationTrack,      0, ruby_AnimationTrack_free,      objs[i]);
      else if (typeid(*objs[i]) == typeid(Appearance))          val_obj = Data_Wrap_Struct(rb_cAppearance,          0, ruby_Appearance_free,          objs[i]);
      else if (typeid(*objs[i]) == typeid(Background))          val_obj = Data_Wrap_Struct(rb_cBackground,          0, ruby_Background_free,          objs[i]);
      else if (typeid(*objs[i]) == typeid(CompositingMode))     val_obj = Data_Wrap_Struct(rb_cCompositingMode,     0, ruby_CompositingMode_free,     objs[i]);
      else if (typeid(*objs[i]) == typeid(Fog))                 val_obj = Data_Wrap_Struct(rb_cFog,                 0, ruby_Fog_free,                 objs[i]);
      else if (typeid(*objs[i]) == typeid(Image2D))             val_obj = Data_Wrap_Struct(rb_cImage2D,             0, ruby_Image2D_free,             objs[i]);
      else if (typeid(*objs[i]) == typeid(TriangleStripArray))  val_obj = Data_Wrap_Struct(rb_cTriangleStripArray,  0, ruby_TriangleStripArray_free,  objs[i]);
      else if (typeid(*objs[i]) == typeid(KeyframeSequence))    val_obj = Data_Wrap_Struct(rb_cKeyframeSequence,    0, ruby_KeyframeSequence_free,    objs[i]);
      else if (typeid(*objs[i]) == typeid(Material))            val_obj = Data_Wrap_Struct(rb_cMaterial,            0, ruby_Material_free,            objs[i]);
      else if (typeid(*objs[i]) == typeid(PolygonMode))         val_obj = Data_Wrap_Struct(rb_cPolygonMode,         0, ruby_PolygonMode_free,         objs[i]);
      else if (typeid(*objs[i]) == typeid(Camera))              val_obj = Data_Wrap_Struct(rb_cCamera,              0, ruby_Camera_free,              objs[i]);
      else if (typeid(*objs[i]) == typeid(Group))               val_obj = Data_Wrap_Struct(rb_cGroup,               0, ruby_Group_free,               objs[i]);
      else if (typeid(*objs[i]) == typeid(World))               val_obj = Data_Wrap_Struct(rb_cWorld,               0, ruby_World_free,               objs[i]);
      else if (typeid(*objs[i]) == typeid(Light))               val_obj = Data_Wrap_Struct(rb_cLight,               0, ruby_Light_free,               objs[i]);
      else if (typeid(*objs[i]) == typeid(Mesh))                val_obj = Data_Wrap_Struct(rb_cMesh,                0, ruby_Mesh_free,                objs[i]);
      else if (typeid(*objs[i]) == typeid(MorphingMesh))        val_obj = Data_Wrap_Struct(rb_cMorphingMesh,        0, ruby_MorphingMesh_free,        objs[i]);
      else if (typeid(*objs[i]) == typeid(SkinnedMesh))         val_obj = Data_Wrap_Struct(rb_cSkinnedMesh,         0, ruby_SkinnedMesh_free,         objs[i]);
      else if (typeid(*objs[i]) == typeid(Sprite3D))            val_obj = Data_Wrap_Struct(rb_cSprite3D,            0, ruby_Sprite3D_free,            objs[i]);
      else if (typeid(*objs[i]) == typeid(Texture2D))           val_obj = Data_Wrap_Struct(rb_cTexture2D,           0, ruby_Texture2D_free,           objs[i]);
      else if (typeid(*objs[i]) == typeid(VertexArray))         val_obj = Data_Wrap_Struct(rb_cVertexArray,         0, ruby_VertexArray_free,         objs[i]);
      else if (typeid(*objs[i]) == typeid(VertexBuffer))        val_obj = Data_Wrap_Struct(rb_cVertexBuffer,        0, ruby_VertexBuffer_free,        objs[i]);
      else 	rb_raise(rb_eRuntimeError, "Loaded object is invalid, name=%s.", typeid(*objs[i]).name());

      objs[i]->setExportedEntity ((void*)val_obj);
      rb_ary_push (val_objs, val_obj);
    }

    return val_objs;
}


/**
 * LoaderクラスのRubyへの登録.
 */
void register_Loader ()
{
    // Loader
    rb_cLoader              = rb_define_class_under (rb_mM3G, "Loader",              rb_cObject);

    rb_define_singleton_method (rb_cLoader, "load", (VALUE(*)(...))ruby_Loader_load, -1);
}
