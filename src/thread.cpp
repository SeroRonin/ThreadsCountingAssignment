#include <iostream>
#include <pthread.h>

class Thread{
    //underlying  thread
    pthread_t thread;
    int uid;
    //should start?
    bool started = false;

    //public:
    //    Thread( int val = 0 ){
    //        thread = newThread;
    //        uid = val;
    //    };

    void start()
    {
        started = true;
    }
    
    void stop()
    {
        started = false;
    }

    void done(){

    }

    int id(){
        return uid;
    }
};