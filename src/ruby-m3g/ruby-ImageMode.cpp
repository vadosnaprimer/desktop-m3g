#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

VALUE ruby_ImageMode_free (Background::ImageMode* ptr)
{
    ptr->~ImageMode ();
    ruby_xfree (ptr);
}


VALUE ruby_ImageMode_set_x (VALUE self, VALUE val_x)
{
  Background::ImageMode* p;
  
  Data_Get_Struct (self, Background::ImageMode, p);

  p->x = FIX2INT (val_x);

  return Qnil;
}

VALUE ruby_ImageMode_set_y (VALUE self, VALUE val_y)
{
  Background::ImageMode* p;
  
  Data_Get_Struct (self, Background::ImageMode, p);

  p->y = FIX2INT (val_y);

  return Qnil;
}

void register_ImageMode ()
{
  // ImageMode
}
