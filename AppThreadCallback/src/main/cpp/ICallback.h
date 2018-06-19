//
// Created by yuhanxun on 2018/6/19.
//

#ifndef SAMPLEJNI_ICALLBACK_H
#define SAMPLEJNI_ICALLBACK_H

#include <string>
class ICallback {
public:
    virtual void onCallback(std::string fileName, bool bOK) = 0;
};


#endif //SAMPLEJNI_ICALLBACK_H
