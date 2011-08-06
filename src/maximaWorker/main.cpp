#include <Ice/Ice.h>
#include <Maxima.h>
#include <string>
#include <maxima_comm.h>

/* *
 * Класс воркера.
 * Воркер должен зарегить себя в диспетчере и обрабатывать запросы к максиме.
 * */
class MaximaWorkerImpl : public MaximaLib::MaximaWorker
{
    private:
        /**
         * Подключение к максиме
         **/
        maxima_comm::MaximaCommunication *comm;

    public:

        /**
         * Конструктор. Если не можем создать коннект к максиме -- вываливаемся с исключением.
         **/
        MaximaWorkerImpl()
        {
            try
            {
                comm = new maxima_comm::MaximaCommunication();
            }
            catch(maxima_comm::MaximaException *ex)
            {
                throw ex->what();
            }
        }

        /**
         * Простейший деструктор
         **/
        virtual ~MaximaWorkerImpl()
        {
            delete comm;
        }

        /**
         * Посчитать строку.
         **/
        virtual std::string calculate(const std::string& s, const Ice::Current&)
        {
            return comm->calculate(s);
        }
};

/**
 * Класс приложения.
 * TODO: Заменить на Сервис.
 **/
class MaximaWorkerApp : public Ice::Application
{
    public:
        /**
         * Главная процедура
         **/
        virtual int run(int, char* [])
        {
            // Получаем адаптер
            Ice::ObjectAdapterPtr adapter = 
                communicator()->createObjectAdapterWithEndpoints("MaximaWorkerAdapter", "default -p 31337");

            //И регистриуем наш объект
            Ice::ObjectPtr object = new MaximaWorkerImpl();
            Ice::ObjectPrx objPrx = adapter->add(object, communicator()->stringToIdentity("MaximaWorker"));
            adapter->activate();

            //Получаем объект диспетчера
            //TODO: приделать сюда указание хоста.
            Ice::ObjectPrx obj = 
                communicator()->stringToProxy("MaximaDispatcher:default -p 31338");
            MaximaLib::MaximaDispatcherPrx disp = MaximaLib::MaximaDispatcherPrx::checkedCast(obj);

            if(!disp)
                throw "Wrong disp";

            // Регистриуемся в диспетчере
            MaximaLib::MaximaWorkerPrx wrkPrx = MaximaLib::MaximaWorkerPrx::uncheckedCast(objPrx);
            disp->registerWorker(wrkPrx);
 
            // Продожаем работать, пока нас не прервут.
            communicator()->waitForShutdown();
        }
};

// Ну тут все понятно,
int main(int argc, char* argv[])
{
    MaximaWorkerApp app;
    return app.main(argc, argv);
}
