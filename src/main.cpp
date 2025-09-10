#include <iostream>
#include <pthread.h>
#include "thread.h"
#include <thread>
#include <mutex>

int THREADCOUNT = 5;
int NUMCOUNT = 1000;

std::mutex count_mutex;
int totalCount = 0;

class CounterThread : public Thread {
    public:
        int selfCount = 0;
        void run() override {
            while(true){
                std::lock_guard<std::mutex> lock(count_mutex);
                if (totalCount >= NUMCOUNT){
                    break;
                }
                totalCount++;
                selfCount++;
                //TODO replace with pthread instead of standard mutex and thread
                std::this_thread::sleep_for(std::chrono::milliseconds(100/NUMCOUNT));
            }
        }
};

int main() {
    std::cout << "Enter Thread Count:";
    std::cin >> THREADCOUNT;

    std::cout << "Enter Target Number:";
    std::cin >> NUMCOUNT;
    //TODO: Validate inputs


    totalCount = 0;
    CounterThread* threadObjs[THREADCOUNT];
    for (int i = 0; i < THREADCOUNT; ++i) {
        CounterThread* newThread = new CounterThread();
        threadObjs[i] = newThread;
        (*newThread).uid = i;
        newThread->start();
    }

    for (int i = 0; i < THREADCOUNT; ++i) {
        pthread_join(threadObjs[i]->thread, nullptr);
    }

    for (int i = 0; i < THREADCOUNT; ++i) {
        std::cout << "Thread [" << threadObjs[i]->id() << "] count:" << threadObjs[i]->selfCount << std::endl;
    } 
    std::cout << "Total count: " << totalCount << std::endl;

    system("pause"); // Pauses the console until a key is pressed
    return 0;
}
