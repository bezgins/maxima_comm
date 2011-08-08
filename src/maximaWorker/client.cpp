#include <Ice/Ice.h>
#include <Maxima.h>
#include <iostream>

/////
// Приложение для проверки Диспетчера.
/////

class MyApp : public Ice::Application
{
    public:
        virtual int run(int, char*[])
        {
            Ice::ObjectPrx obj = 
                communicator()->stringToProxy("MaximaDispatcher:default -p 31338");
            MaximaLib::MaximaDispatcherPrx wrk = MaximaLib::MaximaDispatcherPrx::checkedCast(obj);
            
            if(!wrk)
                throw "Invalid Proxy";

            std::cout << (wrk->calculate("integrate(x/(x^3 + 1), x)")) << std::endl;
        }
};

int main(int argc, char* argv[])
{
    MyApp app;
    return app.main(argc, argv);
}
