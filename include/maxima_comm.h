/*
Copyright (c) 2011, Svyatoslav Bezgin <bezgin@rcbd.org> All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

 *  Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
 *  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
 *  Neither the name of the Tambov State Technical University nor the names of
    its contributors may be used to endorse or promote products derived from this
    software without specific prior written permission.
            
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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

    std::string calculate(const std::string &str);
};



}
#endif
