#include <new>
#include "ruby.h"
#include "Loader.hpp"
using namespace m3g;

VALUE ruby_Loader_free (Loader* ptr)
{
    ptr->~Loader ();
    ruby_xfree (ptr);
}

VALUE ruby_Loader_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Loader));
    return Data_Wrap_Struct (self, NULL, ruby_Loader_free, p);
}

VALUE ruby_Loader_initialize (VALUE self)
{
    Loader* p;
    Data_Get_Struct (self, Loader, p);
    new (p) Loader;
    return Qnil;
}

VALUE binder_Loader_load (int argc, VALUE* argv, VALUE self)
{
    union {
	VALUE val_name;
	VALUE val_data;
    };
    VALUE val_offset;
    VALUE val_array = rb_ary_new ();
        int num = rb_scan_args (argc, argv, "11", &val_name, &val_offset);
    switch (num) {
    case 1: {
	printf ("hikisu 1\n");
	break;
    }
    case 2: {
	printf ("hikisu 2\n");
	break;
    }
    default: {
    }
    }
    // numの数で分岐
    return val_array;
}

// メモ：本来Loaderクラスのインスタンス化(new)は禁止。
// やり方がわからない……
void register_Loader (VALUE rb_cLoader)
{
    // Loader
    rb_define_alloc_func (rb_cLoader, ruby_Loader_allocate);
    rb_define_private_method (rb_cLoader, "initialize", (VALUE(*)(...))ruby_Loader_initialize, 0);

    rb_define_singleton_method (rb_cLoader, "load", (VALUE(*)(...))binder_Loader_load, -1);

}
