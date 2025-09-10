#include <iostream>
#include "thread.h"
#include <pthread.h>

const int THREADCOUNT = 1;
const int NUMCOUNT = 100;

int totalCount = 0;

struct thread_args {
    Thread* threadPtr;
    int* countPtr;
};

void* countFunction(void* args){
    thread_args* input = static_cast<thread_args*>(args);
    Thread* threadInst = static_cast<Thread*>(input->threadPtr);
    int* threadCounter = static_cast<int*>(input->countPtr);
    int threadID = threadInst->uid;
    std::cout << "Thread " << threadID << " is running.\n";
    while (totalCount < NUMCOUNT && threadInst->started){
        totalCount += 1;
        (*threadCounter)++;
        std::cout << "Thread " << threadID << " increasing count to " << (*threadCounter) << ", total: " << totalCount << "\n";
    }
    std::cout << "Thread " << threadID << " is done.\n";
    std::cout << totalCount << "\n";
    return nullptr;
};

int main() {
    //pthread_t threads[THREADCOUNT];
    //int threadIDs[THREADCOUNT];

    //for (int i = 0; i < THREADCOUNT; ++i) {
    //    threadIDs[i] = i;
    //    if (pthread_create(&threads[i], nullptr, countFunction, &threadIDs[i]) != 0) {
    //        std::cerr << "Error creating thread " << i << std::endl;
    //    }
    //}
    
    //for (int i = 0; i < THREADCOUNT; ++i) {
    //    pthread_join(threads[i], nullptr);
    //}

    Thread threads[THREADCOUNT];
    int threadIDs[THREADCOUNT];
    int threadCounts[THREADCOUNT];
    for (int i = 0; i < THREADCOUNT; ++i) {
        Thread newThread = Thread();
        newThread.uid = i;
        threads[i] = newThread;
        threadIDs[i] = i;
        thread_args args = { 
            .threadPtr = &newThread, 
            .countPtr = &threadCounts[i]
        };

        if (pthread_create(&newThread.thread, nullptr, countFunction, &args) != 0) {
           std::cerr << "Error creating thread " << i << std::endl;
        }
        else
        {
            std::cout << "Thread created: " << threads[i].uid << "\n";
        }

        newThread.started = true;
    }

    for (int i = 0; i < THREADCOUNT; ++i) {
        pthread_join(threads[i].thread, nullptr);
    }

    for (int i = 0; i < THREADCOUNT; ++i) {
        std::cout << "Thread ID: " << threads[i].uid << "\n";
    }

    return 0;
}