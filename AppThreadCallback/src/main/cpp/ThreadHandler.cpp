//
// Created by yuhanxun on 2018/6/19.
//

#include "ThreadHandler.h"
using namespace std;
void* runnable(void* threadargs);

pthread_t threads;
void ThreadHandler::start() {
    LOGD("ThreadHandler::start()");

    this->isStop  = false;
    int rc = pthread_create(&threads, NULL,
                            runnable, this);
    if (rc){
        LOGE("Error:unable to create thread");
        exit(-1);
    }
}

void ThreadHandler::stop() {
    this->isStop = true;
}

void ThreadHandler::setCallback(ICallback *callback) {
    this->callback = callback;
}

void* runnable(void* threadargs) {
    ThreadHandler* threadHandler = (ThreadHandler*)threadargs;
    while(!threadHandler->isStop) {
//        LOGD("runnable_xunxunhahahahahahahaha");
//        usleep(500000);
        threadHandler->callback->onCallback("filename",true);
        sleep(1);
    }
    pthread_exit(&threads);
}