//
// Created by yuhanxun on 2018/6/19.
//

#ifndef SAMPLEJNI_THREADHANDLER_H
#define SAMPLEJNI_THREADHANDLER_H

#include <iostream>
#include <cstdlib>
#include <pthread.h>
//#include <thread>
#include <unistd.h>
#include "include/logcat.h"
#include "ICallback.h"

class ThreadHandler {
public:
    void start();
    void stop();
    bool isStop;
    void setCallback(ICallback* callback);
    ICallback* callback;
};


#endif //SAMPLEJNI_THREADHANDLER_H
