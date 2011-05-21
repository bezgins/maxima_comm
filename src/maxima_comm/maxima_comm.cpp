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

#include "maxima_comm.h"
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

namespace maxima_comm
{

std::string MaximaCommunication::calculate(std::string &str)
{
    std::string str1;

    *istream >> str1; // input greeting
//    std::cout << "# " << str1 << std::endl;
 
    *ostream << str << ";" << std::endl;
    ostream->flush();

    *istream >> str1; // output greeting
//    std::cout << "# " << str1 << std::endl;
    *istream >> str1; // actual output
//    std::cout << "# " << str1 << std::endl;

    return str1;
}


MaximaProcess::MaximaProcess()
{

    if((pipe(fd[0]) < 0) || (pipe(fd[1]) < 0))
    {
        throw new MaximaException(sys_errlist[errno]);
    }

    int _pid;

    if((_pid = fork()) < 0)
    {
        throw new MaximaException(sys_errlist[errno]);
    }
    else if(_pid == 0)//Child
    {
        try
        {
            close(fd[0][1]);
            close(fd[1][0]);

            if(fd[0][0] != STDIN_FILENO)
            {
                if(dup2(fd[0][0], STDIN_FILENO) != STDIN_FILENO)
                {
                    throw new MaximaException(sys_errlist[errno]);
                }
                close(fd[0][0]);
            }

            if(fd[1][1] != STDOUT_FILENO)
            {
                if(dup2(fd[1][1], STDOUT_FILENO) != STDOUT_FILENO)
                {
                    throw new MaximaException(sys_errlist[errno]);
                }
                close(fd[1][1]);
            }

            if(execl("/usr/bin/maxima", "maxima", "-q", (char*)0) < 0)
            {
                throw new MaximaException(sys_errlist[errno]);
            }
        }
        catch(MaximaException *ex)
        {
            std::cerr << "Error while starting maxima process: " << ex->what() << std::endl;

            exit(0);

            delete ex;
        }

        return;
    }
    else //Parent
    {
        this->pid = _pid;

        usleep(500);

        pid_t res = waitpid(_pid, NULL, WNOHANG);

        if(res)
            throw new MaximaException("Can not start Maxima Process");
    }
}
}

