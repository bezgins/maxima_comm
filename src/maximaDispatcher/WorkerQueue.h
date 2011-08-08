#ifndef _WorkerQueue_h_included_
#define _WorkerQueue_h_included_

#include <queue>
#include <Maxima.h>
#include <Ice/Ice.h>
#include <IceUtil/Mutex.h>

class WorkerQueue
{
    private:
        // Hide default ctor
        WorkerQueue()
        {
        }

        const IceUtil::Mutex *mutex;

        std::queue<MaximaLib::MaximaWorkerPrx> wrkQueue;


    public:
        WorkerQueue(const IceUtil::Mutex *mutex)
        {
            this->mutex = mutex;
        }

        ~WorkerQueue()
        {
            IceUtil::Mutex::Lock lock(*mutex);

            while(!wrkQueue.empty())
            {
                wrkQueue.pop();
            }
        }

        void addWorker(const MaximaLib::MaximaWorkerPrx& worker)
        {
            IceUtil::Mutex::Lock lock(*mutex);
            wrkQueue.push(worker);

            Ice::Trace tracer(Ice::Application::communicator()->getLogger(), "WorkerQueue::addWorker");
            tracer << "added worker:\t" << (Ice::Application::communicator()->proxyToString(worker));
        }

        const MaximaLib::MaximaWorkerPrx getWorker()
        {
            IceUtil::Mutex::Lock lock(*mutex);

            if(wrkQueue.size() < 1)
                throw "There is no workers!!!";

            MaximaLib::MaximaWorkerPrx result = wrkQueue.front();
            wrkQueue.pop();
            wrkQueue.push(result);

            Ice::Trace tracer(Ice::Application::communicator()->getLogger(), "WorkerQueue::getWorker");
            tracer << "got worker:\t" << (Ice::Application::communicator()->proxyToString(result));
 
            return result;
        }
};

#endif // _WorkerQueue_h_included_
