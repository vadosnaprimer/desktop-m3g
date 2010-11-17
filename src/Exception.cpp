#include "m3g/Exception.hpp"
#include <cstdio>
#include <cstdarg>
using namespace m3g;
using namespace std;

const int size = 1024;

ArithmeticException:: ArithmeticException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

ArithmeticException:: ~ArithmeticException () throw()
{
}

const char* ArithmeticException:: what () const throw()
{
  return msg.c_str();
}


IllegalArgumentException:: IllegalArgumentException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

IllegalArgumentException:: ~IllegalArgumentException () throw()
{
}

const char* IllegalArgumentException:: what () const throw()
{
  return msg.c_str();
}


IllegalStateException:: IllegalStateException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

IllegalStateException:: ~IllegalStateException () throw()
{
}

const char* IllegalStateException:: what () const throw()
{
  return msg.c_str();
}

IndexOutOfBoundsException:: IndexOutOfBoundsException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

IndexOutOfBoundsException:: ~IndexOutOfBoundsException () throw()
{
}

const char* IndexOutOfBoundsException:: what () const throw()
{
  return msg.c_str();
}

IOException:: IOException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

IOException:: ~IOException () throw()
{
}


const char* IOException:: what () const throw()
{
  return msg.c_str();
}

NullPointerException:: NullPointerException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

NullPointerException:: ~NullPointerException () throw()
{
}

const char* NullPointerException:: what () const throw()
{
  return msg.c_str();
}

SecurityException:: SecurityException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

SecurityException:: ~SecurityException () throw()
{
}

const char* SecurityException:: what () const throw()
{
  return msg.c_str();
}

NotImplementedException:: NotImplementedException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

NotImplementedException:: ~NotImplementedException () throw()
{
}

const char* NotImplementedException:: what () const throw()
{
  return msg.c_str();
}

OpenGLException:: OpenGLException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

OpenGLException:: ~OpenGLException () throw()
{
}

const char* OpenGLException:: what () const throw()
{
  return msg.c_str();
}

InternalException:: InternalException (const char* file, const char* func, const char* format, ...)
{
    char buf[size];
    va_list args;
    va_start (args, format);
    vsnprintf (buf, size, format, args);
    va_end (args);
    msg = string(file) + ":" + string(func) + " " + string(buf);
}

InternalException:: ~InternalException () throw()
{
}

const char* InternalException:: what () const throw()
{
  return msg.c_str();
}
