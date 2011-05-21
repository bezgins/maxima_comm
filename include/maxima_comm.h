#ifndef _MAXIMA_COMM_H_INCLUDED_
#define _MAXIMA_COMM_H_INCLUDED_

#include <unistd.h>
#include <string>
#include <iostream>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>

#include "maxima_exc.h"

namespace maxima_comm
{

namespace ios = boost::iostreams;
typedef ios::file_descriptor_source fdsource;
typedef ios::file_descriptor_sink   fdsink;


class MaximaProcess
{
    int fd[2][2];   // File Descriptors for pipe IO
    pid_t pid;      // PID of maxima process
public:
    MaximaProcess();

    int fd_in() const
    {
        return fd[1][0];
    }

    int fd_out() const
    {
        return fd[0][1];
    }
};

class MaximaCommunication
{
    MaximaProcess *process;
    ios::stream<fdsource> *istream;
    ios::stream<fdsink>   *ostream;

public:
    MaximaCommunication()
    {
        process = new MaximaProcess();
        istream = new ios::stream<fdsource>(process->fd_in(), ios::never_close_handle);
        ostream = new ios::stream<fdsink>(process->fd_out(), ios::never_close_handle);

        std::string str;
        *istream >> str; //input greeting
//        std::cout << "| " << str << std::endl;
        *ostream << "display2d:false;" << std::endl;
        ostream->flush();
        *istream >> str; //output greeting
//        std::cout << "| " << str << std::endl;
        *istream >> str; //false output
//        std::cout << "| " << str << std::endl;
    }

    std::string calculate(std::string &str);
};



}
#endif
