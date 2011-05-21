#ifndef _MAXIMA_EXC_H_INCLUDED_
#define _MAXIMA_EXC_H_INCLUDED_

#include <exception>
#include <string>

namespace maxima_comm 
{
    class MaximaException : public std::exception
    {
        std::string cause;

    public:
        MaximaException ()
        {
            cause = "Unknown Exception";
        }

        MaximaException (const char *cause)
        {
            this->cause = cause;
        }

        virtual ~MaximaException() throw()
        {
        }

        virtual const char* what() const throw()
        {
            return this->cause.c_str();
        }
    };
}

#endif
