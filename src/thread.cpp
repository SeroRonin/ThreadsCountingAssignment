
#include <iostream>
#include <pthread.h>
#include "thread.h"

void Thread::start()
{
    pthread_create(&thread, nullptr, threadLogic, this);
}

void Thread::stop()
{
    pthread_cancel(thread);
}

int Thread::id(){
    return uid;
}

void Thread::run() {
}

void Thread::done() {
}

void* Thread::threadLogic(void* arg) {
    Thread* self = static_cast<Thread*>(arg);
    self->run();
    self->done();
    return nullptr;
}