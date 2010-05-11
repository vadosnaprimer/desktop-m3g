#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


void register_Exception ()
{
	rb_eArithmeticException       = rb_define_class_under (rb_mM3G, "ArithmeticException",       rb_eRuntimeError);
	rb_eIllegalArgumentException  = rb_define_class_under (rb_mM3G, "IllegalArgumentException",  rb_eArgError);
	rb_eIllegalStateException     = rb_define_class_under (rb_mM3G, "IllegalStateException",     rb_eRuntimeError);
	rb_eIndexOutOfBoundsException = rb_define_class_under (rb_mM3G, "IndexOutOfBoundsException", rb_eIndexError);
	rb_eIOException               = rb_define_class_under (rb_mM3G, "IOExceptioN",               rb_eIOError);
	rb_eNullPointerException      = rb_define_class_under (rb_mM3G, "NullPointerException",      rb_eRuntimeError);
	rb_eSecurityException         = rb_define_class_under (rb_mM3G, "SecurityException",         rb_eSecurityError);
	rb_eNotImplementedException   = rb_define_class_under (rb_mM3G, "NotImplementedException",   rb_eNotImpError);
	rb_eOpenGLException           = rb_define_class_under (rb_mM3G, "OpenGLException",           rb_eSystemCallError);
	rb_eInternalException         = rb_define_class_under (rb_mM3G, "InternalException",         rb_eFatal);

}


