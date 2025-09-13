#pragma once
#ifndef THREAD_H
#define THREAD_H


class Thread {
    private:
        pthread_t thread;
        int uid;

    public:
        Thread();
        ~Thread();

        bool started;
        void start();
        void stop();

        virtual void run();
        virtual void done();

        void threadSet( pthread_t thread );
        pthread_t threadGet();

        void idSet( int idNew );
        int id();

        static void* threadLogic(void* arg);
};

#endif