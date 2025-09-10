#pragma once
#ifndef THREAD_H
#define THREAD_H


class Thread {
    public:
        pthread_t thread;
        int uid;

        bool started;
        void start();
        void stop();

        virtual void run();
        virtual void done();

        int id();

        static void* threadLogic(void* arg);
};

#endif