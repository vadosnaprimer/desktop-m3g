#include <new>
#include "ruby.h"
#include "Viewport.hpp"
using namespace m3g;


VALUE ruby_Viewport_free (Viewport* ptr)
{
    ptr->~Viewport ();
    ruby_xfree (ptr);
}

VALUE ruby_Viewport_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Viewport));
    return Data_Wrap_Struct (self, NULL, ruby_Viewport_free, p);
}

VALUE ruby_Viewport_initialize (VALUE self)
{
    Viewport* p;
    Data_Get_Struct (self, Viewport, p);
    new (p) Viewport;
    return Qnil;
}

VALUE ruby_Viewport_get_x (VALUE self)
{
    return Qnil;
}

VALUE ruby_Viewport_get_y (VALUE self)
{
    return Qnil;
}

VALUE ruby_Viewport_get_width (VALUE self)
{
    return Qnil;
}

VALUE ruby_Viewport_get_height (VALUE self)
{
    return Qnil;
}


/**
 * Graphics3Dクラスのメンバー関数のRubyへの登録.
 */
void register_Viewport (VALUE rb_cViewport)
{
    // Viewport
    rb_define_alloc_func (rb_cViewport, ruby_Viewport_allocate);
    rb_define_private_method (rb_cViewport, "initialize", (VALUE(*)(...))ruby_Viewport_initialize, 0);

    rb_define_method (rb_cViewport, "x", (VALUE(*)(...))ruby_Viewport_get_x, 0);
    rb_define_method (rb_cViewport, "y", (VALUE(*)(...))ruby_Viewport_get_y, 0);
    rb_define_method (rb_cViewport, "width", (VALUE(*)(...))ruby_Viewport_get_width, 0);
    rb_define_method (rb_cViewport, "height", (VALUE(*)(...))ruby_Viewport_get_height, 0);

}
