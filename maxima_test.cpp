#include <string>
#include <iostream>

#include "maxima_comm.h"

int main()
{
    maxima_comm::MaximaCommunication *comm;

    try
    {
        comm = new maxima_comm::MaximaCommunication();

        std::string s("2+1/2");
        std::cout << s << "=" << comm->calculate(s) << std::endl;
        s = "integrate(x/(x^3 + 1), x)";
        std::cout << s << "=" << comm->calculate(s) << std::endl;
    }
    catch(maxima_comm::MaximaException *ex)
    {
        std::cout << "Exc caught: " << (ex->what()) << std::endl;
        delete ex;
    }

    return 0;
}

