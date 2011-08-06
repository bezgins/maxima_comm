#include <Ice/Ice.h>
#include <Maxima.h>
#include <string>
#include <iostream>


/**
 * Класс, реализующий диспетчера
 **/
class MaximaDispatcherImpl : public MaximaLib::MaximaDispatcher
{
    public:
        /**
         * Вычислить строку на нужном воркере
         **/
        virtual std::string calculate(const std::string& s, const Ice::Current&)
        {
            return "Not implemented";
        }

        /**
         * Зарегать воркера в системе.
         **/
        virtual void registerWorker(const MaximaLib::MaximaWorkerPrx& worker,
                                    const Ice::Current&)
        {
            Ice::Trace tracer(Ice::Application::communicator()->getLogger(), "registerWorker");
            tracer << "registered:" << (Ice::Application::communicator()->proxyToString(worker));
        }

        /**
         * Удалить регистрацию воркера
         **/
        virtual void unregisterWorker(const MaximaLib::MaximaWorkerPrx& worker,
                                    const ::Ice::Current&)
        {
            Ice::Trace tracer(Ice::Application::communicator()->getLogger(), "unregisterWorker");
            tracer << "unregistered:" << (Ice::Application::communicator()->proxyToString(worker));
        }
};

/**
 * Класс приложения
 * TODO: заменить на сервис.
 **/
class MaximaDispatcherApp : public Ice::Application
{
    public:
        /**
         * Главная процедура
         **/
        virtual int run(int, char* [])
        {
            // Получаем адаптер
            Ice::ObjectAdapterPtr adapter = 
                communicator()->createObjectAdapterWithEndpoints("MaximaDispatcherAdapter", "default -p 31338");

            // И регистрируемся в нем
            Ice::ObjectPtr object = new MaximaDispatcherImpl();
            adapter->add(object, communicator()->stringToIdentity("MaximaDispatcher"));
            adapter->activate();

            // продолжаем работать
            communicator()->waitForShutdown();
        }
};

// Тут опять таки все ясно.
int main(int argc, char* argv[])
{
    MaximaDispatcherApp app;
    return app.main(argc, argv);
}
