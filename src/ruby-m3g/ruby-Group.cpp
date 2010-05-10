#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


namespace {
  struct ChildAccessor {
    Group* group;
  };
  VALUE rb_cGroup_ChildAccessor;
}

VALUE ruby_Group_free (Group* ptr)
{
    ptr->~Group ();
    ruby_xfree (ptr);
}

VALUE ruby_Group_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Group));
    return Data_Wrap_Struct (self, 0, ruby_Group_free, p);
}

VALUE ruby_Group_initialize (VALUE self)
{
    Group* p;
    Data_Get_Struct (self, Group, p);
    new (p) Group;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Group_add_child (VALUE self, VALUE val_child)
{
    Group* p;
    Node* child;

    Data_Get_Struct (self, Group, p);
    Data_Get_Struct (val_child, Group, child);

    p->addChild (child);

    return Qnil;
}

VALUE ruby_Group_get_child (VALUE self)
{
    Group* p;
    ChildAccessor* accessor;
    VALUE val_accessor;

    Data_Get_Struct (self, Group, p);
    val_accessor = Data_Make_Struct (rb_cGroup_ChildAccessor, ChildAccessor, 0, -1, accessor);
    accessor->group = p;

    return val_accessor;
}

VALUE ruby_Group_get_child_count (VALUE self)
{
    Group* p;
    int count;

    Data_Get_Struct (self, Group, p);
    count = p->getChildCount();

    return INT2NUM(count);
}

VALUE ruby_Group_pick (VALUE self, VALUE val_scope, VALUE val_ox, VALUE val_oy, VALUE val_oz, VALUE val_dx, VALUE val_dy, VALUE val_dz, VALUE val_ri)
{
    Group* p;
    Data_Get_Struct (self, Group, p);
    int   scope = NUM2INT (val_scope);
    float ox    = NUM2DBL(val_ox);
    float oy    = NUM2DBL(val_oy);
    float oz    = NUM2DBL(val_oz);
    float dx    = NUM2DBL(val_dx);
    float dy    = NUM2DBL(val_dy);
    float dz    = NUM2DBL(val_dz);
    RayIntersection* ri;
    Data_Get_Struct (val_ri, RayIntersection, ri);

    bool picked = p->pick (scope, ox, oy, oz, dx, dy, dz, ri);

    return picked ? Qtrue : Qfalse;
}

VALUE ruby_Group_remove_child (VALUE self, VALUE val_child)
{
    Group* p;
    Data_Get_Struct (self, Group, p);
    Node* child;
    Data_Get_Struct (val_child, Node, child);

    p->removeChild (child);

    return Qnil;
}


/**
 * Group_ChildAccessor
 */

VALUE ruby_Group_ChildAccessor_get_child (VALUE self, VALUE val_index)
{
   ChildAccessor* p;
    Data_Get_Struct (self, ChildAccessor, p);
   int   index = NUM2INT (val_index);
   Node* child = p->group->getChild (index);
    
    return child ? (VALUE)child->getExportedEntity() : Qnil;
 }


void register_Group ()
{
     // Group
    rb_cGroup               = rb_define_class_under (rb_mM3G, "Group",               rb_cNode);

     rb_define_alloc_func (rb_cGroup, ruby_Group_allocate);
     rb_define_private_method (rb_cGroup, "initialize", (VALUE(*)(...))ruby_Group_initialize, 0);

     rb_define_method (rb_cGroup, "add_child",      (VALUE(*)(...))ruby_Group_add_child, 1);
     rb_define_method (rb_cGroup, "child",          (VALUE(*)(...))ruby_Group_get_child, 0);
     rb_define_method (rb_cGroup, "child_count",    (VALUE(*)(...))ruby_Group_get_child_count, 0);
     rb_define_method (rb_cGroup, "pick",           (VALUE(*)(...))ruby_Group_pick, 8);
     rb_define_method (rb_cGroup, "remove_child",   (VALUE(*)(...))ruby_Group_remove_child, 1);

     // Group_ChildAcdessor
     rb_cGroup_ChildAccessor  = rb_define_class_under (rb_cGroup, "ChildAccessor", rb_cObject);

     rb_define_method (rb_cGroup_ChildAccessor, "[]",        (VALUE(*)(...))ruby_Group_ChildAccessor_get_child,    1);
}
