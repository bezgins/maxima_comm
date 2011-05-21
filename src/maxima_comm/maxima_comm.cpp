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

