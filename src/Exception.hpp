
#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <exception>
#include <string>

namespace m3g {


    class ArithmeticException : public std::exception
    {
    public:
        explicit ArithmeticException (const char* file, const char* func, const char* format, ...);
        virtual ~ArithmeticException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class IllegalArgumentException : public std::exception
    {
    public:
        explicit IllegalArgumentException (const char* file, const char* func, const char* format, ...);
        virtual ~IllegalArgumentException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class IllegalStateException : public std::exception
    {
    public:
        explicit IllegalStateException (const char* file, const char* func, const char* format, ...);
        virtual ~IllegalStateException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class IndexOutOfBoundsException : public std::exception
    {
    public:
        explicit IndexOutOfBoundsException (const char* file, const char* func, const char* format, ...);
        virtual ~IndexOutOfBoundsException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class IOException : public std::exception
    {
    public:
        explicit IOException (const char* file, const char* func, const char* format, ...);
        virtual ~IOException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class NullPointerException : public std::exception
    {
    public:
        explicit NullPointerException (const char* file, const char* func, const char* format, ...);
        virtual ~NullPointerException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class SecurityException : public std::exception
    {
    public:
        explicit SecurityException (const char* file, const char* func, const char* format, ...);
        virtual ~SecurityException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class NotImplementedException : public std::exception
    {
    public:
        explicit NotImplementedException (const char* file, const char* func, const char* format, ...);
        virtual ~NotImplementedException () throw();
        virtual const char* what () const throw();

        std::string msg;
    };

    class OpenGLException : public std::exception
    {
    public:
        explicit OpenGLException (const char* file, const char* func, const char* format, ...);
        virtual ~OpenGLException () throw();
        virtual const char* what () const throw();

        std::string msg;
    }; 

    class InternalException : public std::exception
    {
    public:
        explicit InternalException (const char* file, const char* func, const char* format, ...);
        virtual ~InternalException () throw();
        virtual const char* what () const throw();

        std::string msg;
    }; 

} // namespace m3g {

#endif
