#include <new>
#include "ruby.h"
#include "ActiveInterval.hpp"
using namespace m3g;


VALUE ruby_ActiveInterval_free (ActiveInterval* ptr)
{
    ptr->~ActiveInterval ();
    ruby_xfree (ptr);
}

VALUE ruby_ActiveInterval_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(ActiveInterval));
    return Data_Wrap_Struct (self, NULL, ruby_ActiveInterval_free, p);
}

VALUE ruby_ActiveInterval_initialize (VALUE self)
{
    ActiveInterval* p;
    Data_Get_Struct (self, ActiveInterval, p);
    new (p) ActiveInterval;
    return Qnil;
}

VALUE ruby_ActiveInterval_get_start (VALUE self)
{
    return Qnil;
}
VALUE ruby_ActiveInterval_set_start (VALUE self, VALUE val_start)
{
    return Qnil;
}
VALUE ruby_ActiveInterval_get_end (VALUE self)
{
    return Qnil;
}
VALUE ruby_ActiveInterval_set_end (VALUE self, VALUE val_end)
{
    return Qnil;
}


void register_ActiveInterval (VALUE rb_cActiveInterval)
{
    // AnimationController:: ActiveInterval
    rb_define_alloc_func (rb_cActiveInterval, ruby_ActiveInterval_allocate);
    rb_define_private_method (rb_cActiveInterval, "initialize", (VALUE(*)(...))ruby_ActiveInterval_initialize, 0);

    rb_define_method (rb_cActiveInterval, "start",  (VALUE(*)(...))ruby_ActiveInterval_get_start, 0);
    rb_define_method (rb_cActiveInterval, "start=", (VALUE(*)(...))ruby_ActiveInterval_set_start, 1);
    rb_define_method (rb_cActiveInterval, "end",    (VALUE(*)(...))ruby_ActiveInterval_get_end, 0);
    rb_define_method (rb_cActiveInterval, "end=",   (VALUE(*)(...))ruby_ActiveInterval_set_end, 1);

}
