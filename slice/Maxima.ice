module MaximaLib
{
    interface MaximaWorker
    {
        string calculate(string s);
    };

    interface MaximaDispatcher
    {
        void registerWorker(MaximaWorker *worker);
        void unregisterWorker(MaximaWorker *worker);
        string calculate(string s);
    };
};

