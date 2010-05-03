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
    return Data_Wrap_Struct (self, NULL, ruby_Node_free, p);
}

VALUE ruby_Node_initialize (VALUE self)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    new (p) Node;
    return Qnil;
}

VALUE ruby_Node_align (VALUE self, VALUE reference)
{
    return Qnil;
}

VALUE ruby_Node_get_alignment_reference (VALUE self, VALUE val_axis)
{
    return Qnil;
}

VALUE ruby_Node_get_alignment_target (VALUE self, VALUE val_axis)
{
    return Qnil;    
}

VALUE ruby_Node_get_alpha_factor (VALUE self)
{
    return Qnil;    
}

VALUE ruby_Node_get_parent (VALUE self)
{
    return Qnil;    
}

VALUE ruby_Node_get_scope (VALUE self)
{
    return Qnil;    
}

VALUE ruby_Node_get_transform_to (VALUE self, VALUE val_target, VALUE val_transform)
{
    return Qnil;
}

VALUE ruby_Node_is_picking_enabled (VALUE self)
{
    return Qnil;    
}

VALUE ruby_Node_is_rendering_enabled (VALUE self)
{
    return Qnil;    
}

VALUE ruby_Node_set_alignment (VALUE self, VALUE val_zRef_and_zTarget_and_yRef_and_yTarget)
{
    return Qnil;
}

VALUE ruby_Node_set_alpha_factor (VALUE self, VALUE val_alpha_factor)
{
    return Qnil;    
}

VALUE ruby_Node_set_picking_enable (VALUE self, VALUE val_enable)
{
    return Qnil;    
}

VALUE ruby_Node_set_rendering_enable (VALUE self, VALUE val_enable)
{
    return Qnil;
}

VALUE ruby_Node_set_scope (VALUE self, VALUE val_scope)
{
    return Qnil;    
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
     rb_define_method (rb_cNode, "alignment=",           (VALUE(*)(...))ruby_Node_set_alignment, 1);
     rb_define_method (rb_cNode, "alpha_factor=",        (VALUE(*)(...))ruby_Node_set_alpha_factor, 1);
     rb_define_method (rb_cNode, "picking_enable=",      (VALUE(*)(...))ruby_Node_set_picking_enable, 1);
     rb_define_method (rb_cNode, "rendering_enable=",    (VALUE(*)(...))ruby_Node_set_rendering_enable, 1);
     rb_define_method (rb_cNode, "scope=",               (VALUE(*)(...))ruby_Node_set_scope, 1);


}
