#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
    struct AlignmentAccessor {
        Node* node;
    };
    struct TargetReferenceAccessor {
        Node* node;
        int   axis;
    };
    VALUE rb_cNode_AlignmentAccessor;
    VALUE rb_cNode_TargetReferenceAccessor;
}

VALUE ruby_Node_free (Node* ptr)
{
    __TRY__;
    ptr->~Node ();
    __CATCH__;
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
    __TRY__;
    new (p) Node;
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Node_align (VALUE self, VALUE val_reference)
{
    Node* p;
    Node* ref;

    Data_Get_Struct (self, Node, p);
    Data_Get_Struct (val_reference, Node, ref);
    __TRY__;
    p->align (ref);
    __CATCH__;

    return Qnil;
}

VALUE ruby_Node_get_alignment (VALUE self)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    AlignmentAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cNode_AlignmentAccessor, AlignmentAccessor, 0, -1, accessor);
    accessor->node = p;
    return val_accessor;
}


VALUE ruby_Node_get_alpha_factor (VALUE self)
{
    Node* p;
    float alpha;

    Data_Get_Struct (self, Node, p);
    __TRY__;
    alpha = p->getAlphaFactor ();
    __CATCH__;

    return rb_float_new(alpha);    
}

VALUE ruby_Node_get_parent (VALUE self)
{
    Node* p;
    Node* parent;

    Data_Get_Struct (self, Node, p);
    __TRY__;
    parent = p->getParent ();
    __CATCH__;

    return (VALUE)parent->getExportedEntity();
}

VALUE ruby_Node_get_scope (VALUE self)
{
    Node* p;
    int scope;

    Data_Get_Struct (self, Node, p);
    __TRY__;
    scope = p->getScope();
    __CATCH__;

    return INT2NUM(scope);
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
    __TRY__;
    ret = p->getTransformTo (target, trans);
    __CATCH__;

    return ret ? Qtrue : Qfalse;
}

VALUE ruby_Node_is_picking_enabled (VALUE self)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    bool enabled;
    __TRY__;
    enabled = p->isPickingEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qnil;    
}

VALUE ruby_Node_is_rendering_enabled (VALUE self)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    bool enabled;
    __TRY__;
    enabled = p->isRenderingEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_Node_set_alignment (VALUE self, VALUE val_z_ref, VALUE val_z_target, VALUE val_y_ref, VALUE val_y_target)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    Node* z_ref, *y_ref;
    Data_Get_Struct (val_z_ref, Node, z_ref);    
    Data_Get_Struct (val_y_ref, Node, y_ref);
    int z_target, y_target;
    z_target = NUM2INT (val_z_ref);
    y_target = NUM2INT (val_y_ref);
    __TRY__;
    p->setAlignment (z_ref, z_target, y_ref, y_target);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Node_set_alpha_factor (VALUE self, VALUE val_alpha_factor)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    float alpha = NUM2DBL(val_alpha_factor);
    __TRY__;
    p->setAlphaFactor (alpha);
    __CATCH__;
    return Qnil;    
}

VALUE ruby_Node_set_picking_enable (VALUE self, VALUE val_enable)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    bool enabled = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setPickingEnable (enabled);
    __CATCH__;
    return Qnil;    
}

VALUE ruby_Node_set_rendering_enable (VALUE self, VALUE val_enable)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    bool  enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setRenderingEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Node_set_scope (VALUE self, VALUE val_scope)
{
    Node* p;
    Data_Get_Struct (self, Node, p);
    int scope = INT2NUM (scope);
    __TRY__;
    p->setScope (scope);
    __CATCH__;
    return scope;
}

/**
 * Node_AlignmentAccessor
 */

VALUE ruby_Node_AlignmentAccessor_get_alignment (VALUE self, VALUE val_axis)
{
    AlignmentAccessor* p;
    Data_Get_Struct (self, AlignmentAccessor, p);
    TargetReferenceAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cNode_TargetReferenceAccessor, TargetReferenceAccessor, 0, -1, accessor);
    accessor->node = p->node;
    accessor->axis = NUM2INT(val_axis);
    return val_accessor;
}

/**
 * Node::TargetReferenceAccessor
 */
VALUE ruby_Node_TargetReferenceAccessor_get_target (VALUE self)
{
    TargetReferenceAccessor* p;
    Data_Get_Struct (self, TargetReferenceAccessor, p);
    int target;
    __TRY__;
    target = p->node->getAlignmentTarget (p->axis);
    __CATCH__;
    return INT2NUM(target);
}

VALUE ruby_Node_TargetReferenceAccessor_get_reference (VALUE self)
{
    TargetReferenceAccessor* p;
    Data_Get_Struct (self, TargetReferenceAccessor, p);
    Node* ref;
    __TRY__;
    ref = p->node->getAlignmentReference (p->axis);
    __CATCH__;
    return ref ? (VALUE)ref->getExportedEntity() : Qnil;
}



void register_Node ()
{
    // Node
    rb_cNode                = rb_define_class_under (rb_mM3G, "Node",                rb_cTransformable);

    rb_define_const (rb_cNode, "NONE",   INT2NUM(Node::NONE));
    rb_define_const (rb_cNode, "ORIGIN", INT2NUM(Node::ORIGIN));
    rb_define_const (rb_cNode, "X_AXIS", INT2NUM(Node::X_AXIS));
    rb_define_const (rb_cNode, "Y_AXIS", INT2NUM(Node::Y_AXIS));
    rb_define_const (rb_cNode, "Z_AXIS", INT2NUM(Node::Z_AXIS));

    rb_define_alloc_func (rb_cNode, ruby_Node_allocate);
    rb_define_private_method (rb_cNode, "initialize",  (VALUE(*)(...))ruby_Node_initialize, 0);

    rb_define_method (rb_cNode, "align",               (VALUE(*)(...))ruby_Node_align,                1);
    rb_define_method (rb_cNode, "alignment",           (VALUE(*)(...))ruby_Node_get_alignment,        0);
    rb_define_method (rb_cNode, "alpha_factor",        (VALUE(*)(...))ruby_Node_get_alpha_factor,     0);
    rb_define_method (rb_cNode, "parent",              (VALUE(*)(...))ruby_Node_get_parent,           0);
    rb_define_method (rb_cNode, "scope",               (VALUE(*)(...))ruby_Node_get_scope,            0);
    rb_define_method (rb_cNode, "transform_to",        (VALUE(*)(...))ruby_Node_get_transform_to,     2);
    rb_define_method (rb_cNode, "picking_enabled?",    (VALUE(*)(...))ruby_Node_is_picking_enabled,   0);
    rb_define_method (rb_cNode, "rendering_enabled?",  (VALUE(*)(...))ruby_Node_is_rendering_enabled, 0);
    rb_define_method (rb_cNode, "set_alignment",       (VALUE(*)(...))ruby_Node_set_alignment,        4);
    rb_define_method (rb_cNode, "alpha_factor=",       (VALUE(*)(...))ruby_Node_set_alpha_factor,     1);
    rb_define_method (rb_cNode, "picking_enable=",     (VALUE(*)(...))ruby_Node_set_picking_enable,   1);
    rb_define_method (rb_cNode, "rendering_enable=",   (VALUE(*)(...))ruby_Node_set_rendering_enable, 1);
    rb_define_method (rb_cNode, "scope=",              (VALUE(*)(...))ruby_Node_set_scope,            1);

    // Node::AlignmentAccessor
    rb_cNode_AlignmentAccessor  = rb_define_class_under (rb_cNode, "AlignmentAccessor", rb_cObject);

    rb_define_method (rb_cNode_AlignmentAccessor, "[]",        (VALUE(*)(...))ruby_Node_AlignmentAccessor_get_alignment,    1);

    // Node::TargetReferenceAccessor
    rb_cNode_TargetReferenceAccessor  = rb_define_class_under (rb_cNode, "TargetReferenceAccessor", rb_cObject);

    rb_define_method (rb_cNode_TargetReferenceAccessor, "target",        (VALUE(*)(...))ruby_Node_TargetReferenceAccessor_get_target,    0);
    rb_define_method (rb_cNode_TargetReferenceAccessor, "reference",     (VALUE(*)(...))ruby_Node_TargetReferenceAccessor_get_reference, 0);
}
