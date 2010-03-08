#include <new>
#include "ruby.h"
#include "Group.hpp"
using namespace m3g;

VALUE ruby_Group_free (Group* ptr)
{
    ptr->~Group ();
    ruby_xfree (ptr);
}

VALUE ruby_Group_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Group));
    return Data_Wrap_Struct (self, NULL, ruby_Group_free, p);
}

VALUE ruby_Group_initialize (VALUE self)
{
    Group* p;
    Data_Get_Struct (self, Group, p);
    new (p) Group;
    return Qnil;
}

VALUE ruby_Group_add_child (VALUE self, VALUE val_child)
{
    return Qnil;
}

VALUE ruby_Group_get_child (VALUE self, VALUE val_index)
{
    return Qnil;
}

VALUE ruby_Group_get_child_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_Group_pick (VALUE self, VALUE val_scope, VALUE val_ox, VALUE val_oy, VALUE val_oz, VALUE val_dx, VALUE val_dy, VALUE val_dz, VALUE val_ri)
{
    return Qnil;
}

VALUE ruby_Group_remove_child (VALUE self, VALUE val_child)
{
    return Qnil;
}

void register_Group (VALUE rb_cGroup)
{
     // Group
     rb_define_alloc_func (rb_cGroup, ruby_Group_allocate);
     rb_define_private_method (rb_cGroup, "initialize", (VALUE(*)(...))ruby_Group_initialize, 0);

     rb_define_method (rb_cGroup, "add_child",      (VALUE(*)(...))ruby_Group_add_child, 1);
     rb_define_method (rb_cGroup, "child",          (VALUE(*)(...))ruby_Group_get_child, 1);
     rb_define_method (rb_cGroup, "child_count",    (VALUE(*)(...))ruby_Group_get_child_count, 0);
     rb_define_method (rb_cGroup, "pick",           (VALUE(*)(...))ruby_Group_pick, 8);
     rb_define_method (rb_cGroup, "remove_child",   (VALUE(*)(...))ruby_Group_remove_child, 1);


}
