#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

extern VALUE ruby_Object3D_free (Object3D* ptr);


VALUE ruby_Loader_load (int argc, VALUE* argv, VALUE self)
{
  Loader* p;
  Data_Get_Struct (self, Loader, p);

  std::vector<Object3D*> objs;

  VALUE val_arg1, val_arg2, val_arg3;

  int num = rb_scan_args (argc, argv, "12", &val_arg1, &val_arg2, &val_arg3);
    switch (num) {
    case 1: {
      const char* name = STR2CSTR (val_arg1);
      objs =  p->load (name);
      break;
    }
    case 3: {
      int length       = FIX2INT (val_arg1);
      const char* data = STR2CSTR (val_arg2);
      int offset       = FIX2INT (val_arg3);
      objs = p->load (length, data, offset);
      break;
    }
    default: {
      // えらー
    }
    }

    VALUE val_objs = rb_ary_new ();
    for (int i = 0; i < (int)objs.size(); i++) {
      VALUE val_obj;
      val_obj = Data_Wrap_Struct (rb_cObject3D, 0, ruby_Object3D_free, objs[i]);
      objs[i]->setExportedEntity ((void*)val_obj);
      rb_ary_push (val_objs, val_obj);
    }

    return val_objs;
}

// メモ：本来Loaderクラスのインスタンス化(new)は禁止。
// やり方がわからない……
void register_Loader ()
{
    // Loader
    //rb_define_alloc_func (rb_cLoader, ruby_Loader_allocate);
    //rb_define_private_method (rb_cLoader, "initialize", (VALUE(*)(...))ruby_Loader_initialize, 0);

    rb_define_singleton_method (rb_cLoader, "load", (VALUE(*)(...))ruby_Loader_load, -1);
}
