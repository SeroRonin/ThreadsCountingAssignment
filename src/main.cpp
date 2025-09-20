#include <iostream>
#include <mutex>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <thread>
#include <pthread.h>
#include "thread.h"

int THREADCOUNT = 5;
int TARGETNUM = 1000;

std::mutex count_mutex;
int totalCount = 0;

class CounterThread : public Thread {
    public:
        int selfCountTarget = 0;
        int selfCount = 0;
        void run() override {
            while(true){
                std::lock_guard<std::mutex> lock(count_mutex);
                if (selfCount >= selfCountTarget || totalCount >= TARGETNUM){
                    break;
                }
                totalCount++;
                selfCount++;
            }
        }
};

std::vector<int> splitNumberIntoRandomParts(int numTotal, int splitCount) {
    if (numTotal <= 0 || splitCount <= 0) {
        return {};
    }

    if (splitCount == 1) {
        return {numTotal};
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> parts(splitCount);

    if ( numTotal == 1 ) {
        parts[0] = 1;
        for (int i = 1; i < splitCount; ++i) {
            parts[i] = 0;
        }
    }
    else {
        std::vector<int> splitPoint;
        for (int i = 0; i < splitCount - 1; ++i) {
            std::uniform_int_distribution<> distrib(1, numTotal - 1);
            splitPoint.push_back(distrib(gen));
        }

        std::sort(splitPoint.begin(), splitPoint.end());

        parts[0] = splitPoint[0];
        for (int i = 1; i < splitCount - 1; ++i) {
            parts[i] = splitPoint[i] - splitPoint[i-1];
        }
        parts[splitCount - 1] = numTotal - splitPoint[splitCount - 2];
    }

    std::shuffle(parts.begin(), parts.end(), gen);

    return parts;
}

int getValidatedInt(const std::string& prompt) {
    int value = 1;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value <= 0) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Please enter a positive integer.\n";
        } else {
            std::cin.ignore();
            return value;
        }
    }
}

int main() {
    THREADCOUNT = getValidatedInt("Enter Thread Count: ");
    TARGETNUM = getValidatedInt("Enter Target Number: ");

    totalCount = 0;
    std::vector<int> threadNumAssignments = splitNumberIntoRandomParts( TARGETNUM, THREADCOUNT );
    CounterThread* threadObjs[THREADCOUNT];
    for (int i = 0; i < THREADCOUNT; ++i) {
        CounterThread* newThread = new CounterThread();
        threadObjs[i] = newThread;
        newThread->idSet(i);
        newThread->selfCountTarget = threadNumAssignments[i];
        newThread->start();
    }

    for (int i = 0; i < THREADCOUNT; ++i) {
        pthread_join(threadObjs[i]->threadGet(), nullptr);
    }

    for (int i = 0; i < THREADCOUNT; ++i) {
        std::cout << "Thread " << threadObjs[i]->id() << " [" << threadObjs[i]->threadGet() << "]: Counted " << threadObjs[i]->selfCount << std::endl;
    } 
    std::cout << "Total count: " << totalCount << std::endl;

    for (int i = 0; i < THREADCOUNT; ++i) {
        delete(threadObjs[i]);
    }
    
    std::cout << "Program completed. Press enter to close the terminal" << std::endl;
    std::cin.get();
    return 0;
}
