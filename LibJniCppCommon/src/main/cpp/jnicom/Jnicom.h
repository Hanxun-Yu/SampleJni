//
// Created by yuhanxun on 2018/6/15.
//

#ifndef SAMPLEJNI_JNICOM_H
#define SAMPLEJNI_JNICOM_H

#include <jni.h>
#include <string>

class Jnicom {
public:
    Jnicom(JNIEnv *env);
    const char* strValOf(std::string str);
    const char* strValOf(std::string str,bool isCopy);
    std::string strValOf(char* p);

    std::string strValOf(jstring str);
    std::string strValOf(jstring str,bool isCopy);
    jstring jstrValOf(std::string str);

    int* jintValOf(jintArray intArr);
    jcharArray jcharValOf(const char* charArr);

    jbyteArray jbyteValOf(std::string str);
    jbyteArray jbyteValOf(const char* charArr,int length);
private:
    JNIEnv *env;
};


#endif //SAMPLEJNI_JNICOM_H
