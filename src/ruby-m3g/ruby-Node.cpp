#include <new>
#include "ruby.h"
#include "Node.hpp"
using namespace m3g;

VALUE ruby_Node_free (Node* ptr)
{
    ptr->~Node ();
    ruby_xfree (ptr);
}

VALUE ruby_Node_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Node));
    return Data_Wrap_Struct (self, 0, ruby_Node_free, p);
}

VALUE ruby_Node_initialize (VALUE self)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    new (p) Node;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Node_align (VALUE self, VALUE val_reference)
{
    Node* p;
    Node* ref;

    Data_Get_Struct (self, Node, p);
    Data_Get_Struct (val_reference, Node, ref);
    
    p->align (ref);

    return Qnil;
}

VALUE ruby_Node_get_alignment_reference (VALUE self, VALUE val_axis)
{
    Node* p;
    int axis;
    Node* ref;

    Data_Get_Struct (self, Node, p);
    axis = FIX2INT (val_axis);

    ref = p->getAlignmentReference (axis);

    return (VALUE)ref->getExportedEntity();
}

VALUE ruby_Node_get_alignment_target (VALUE self, VALUE val_axis)
{
    Node* p;
    int axis;
    int target;

    Data_Get_Struct (self, Node, p);
    axis = FIX2INT (val_axis);

    target = p->getAlignmentTarget (axis);

    return INT2FIX(target);
}

VALUE ruby_Node_get_alpha_factor (VALUE self)
{
    Node* p;
    float alpha;

    Data_Get_Struct (self, Node, p);

    alpha = p->getAlphaFactor ();

    return rb_float_new(alpha);    
}

VALUE ruby_Node_get_parent (VALUE self)
{
    Node* p;
    Node* parent;

    Data_Get_Struct (self, Node, p);

    parent = p->getParent ();

    return (VALUE)parent->getExportedEntity();
}

VALUE ruby_Node_get_scope (VALUE self)
{
    Node* p;
    int scope;

    Data_Get_Struct (self, Node, p);
    scope = p->getScope();

    return INT2FIX(scope);
}

VALUE ruby_Node_get_transform_to (VALUE self, VALUE val_target, VALUE val_transform)
{
    Node* p;
    Node* target;
    Transform* trans;
    bool ret;

    Data_Get_Struct (self, Node, p);
    Data_Get_Struct (val_target, Node, target);
    Data_Get_Struct (val_transform, Transform, trans);

    ret = p->getTransformTo (target, trans);

    if (ret)
      return Qtrue;
    else
      return Qfalse;
}

VALUE ruby_Node_is_picking_enabled (VALUE self)
{
    Node* p;
    bool enabled;

    Data_Get_Struct (self, Node, p);

    enabled = p->isPickingEnabled ();

    if (enabled)
      return Qtrue;
    else
      return Qnil;    
}

VALUE ruby_Node_is_rendering_enabled (VALUE self)
{
    Node* p;
    bool enabled;

    Data_Get_Struct (self, Node, p);
    
    enabled = p->isRenderingEnabled ();

    if (enabled)
      return Qtrue;
    else
      return Qfalse;
}

VALUE ruby_Node_set_alignment (VALUE self, VALUE val_z_ref, VALUE val_z_target, VALUE val_y_ref, VALUE val_y_target)
{
    Node* p;
    Node* z_ref, *y_ref;
    int z_target, y_target;

    Data_Get_Struct (self, Node, p);
    Data_Get_Struct (val_z_ref, Node, z_ref);    
    z_target = FIX2INT (val_z_ref);
    Data_Get_Struct (val_y_ref, Node, y_ref);
    y_target = FIX2INT (val_y_ref);

    p->setAlignment (z_ref, z_target, y_ref, y_target);

    return Qnil;
}

VALUE ruby_Node_set_alpha_factor (VALUE self, VALUE val_alpha_factor)
{
    Node* p;
    float alpha;

    Data_Get_Struct (self, Node, p);
    alpha = RFLOAT_VALUE(val_alpha_factor);

    p->setAlphaFactor (alpha);

    return Qnil;    
}

VALUE ruby_Node_set_picking_enable (VALUE self, VALUE val_enable)
{
    Node* p;
    bool enabled;

    Data_Get_Struct (self, Node, p);
    enabled = (val_enable == Qtrue) ? true : false;

    p->setPickingEnable (enabled);

    return Qnil;    
}

VALUE ruby_Node_set_rendering_enable (VALUE self, VALUE val_enable)
{
    Node* p;
    bool  enable;

    Data_Get_Struct (self, Node, p);
    enable = (val_enable == Qtrue) ? true : false;

    p->setRenderingEnable (enable);

    return Qnil;
}

VALUE ruby_Node_set_scope (VALUE self, VALUE val_scope)
{
    Node* p;
    int scope;

    Data_Get_Struct (self, Node, p);
    scope = INT2FIX (scope);

    p->setScope (scope);

    return scope;
}

void register_Node (VALUE rb_cNode)
{
     // Node
     rb_define_const (rb_cNode, "NONE",   INT2FIX(Node::NONE));
     rb_define_const (rb_cNode, "ORIGIN", INT2FIX(Node::ORIGIN));
     rb_define_const (rb_cNode, "X_AXIS", INT2FIX(Node::X_AXIS));
     rb_define_const (rb_cNode, "Y_AXIS", INT2FIX(Node::Y_AXIS));
     rb_define_const (rb_cNode, "Z_AXIS", INT2FIX(Node::Z_AXIS));

     rb_define_alloc_func (rb_cNode, ruby_Node_allocate);
     rb_define_private_method (rb_cNode, "initialize", (VALUE(*)(...))ruby_Node_initialize, 0);

     rb_define_method (rb_cNode, "align",               (VALUE(*)(...))ruby_Node_align, 1);
     rb_define_method (rb_cNode, "alignment_reference", (VALUE(*)(...))ruby_Node_get_alignment_reference, 1);
     rb_define_method (rb_cNode, "alignment_target",    (VALUE(*)(...))ruby_Node_get_alignment_target, 1);
     rb_define_method (rb_cNode, "alpha_factor",        (VALUE(*)(...))ruby_Node_get_alpha_factor, 0);
     rb_define_method (rb_cNode, "parent",              (VALUE(*)(...))ruby_Node_get_parent, 0);
     rb_define_method (rb_cNode, "scope",               (VALUE(*)(...))ruby_Node_get_scope, 0);
     rb_define_method (rb_cNode, "transform_to",        (VALUE(*)(...))ruby_Node_get_transform_to, 2);
     rb_define_method (rb_cNode, "picking_enabled?",     (VALUE(*)(...))ruby_Node_is_picking_enabled, 0);
     rb_define_method (rb_cNode, "rendering_enabled?",   (VALUE(*)(...))ruby_Node_is_rendering_enabled, 0);
     rb_define_method (rb_cNode, "set_alignment",           (VALUE(*)(...))ruby_Node_set_alignment, 4);
     rb_define_method (rb_cNode, "alpha_factor=",        (VALUE(*)(...))ruby_Node_set_alpha_factor, 1);
     rb_define_method (rb_cNode, "picking_enable=",      (VALUE(*)(...))ruby_Node_set_picking_enable, 1);
     rb_define_method (rb_cNode, "rendering_enable=",    (VALUE(*)(...))ruby_Node_set_rendering_enable, 1);
     rb_define_method (rb_cNode, "scope=",               (VALUE(*)(...))ruby_Node_set_scope, 1);


}
