//
// Created by yuhanxun on 2018/6/15.
//

#include <cstdlib>
#include "Jnicom.h"

Jnicom::Jnicom(JNIEnv *env) {
    this->env = env;
}
Jnicom::Jnicom() {
}

const char *Jnicom::strValOf(std::string str) {
    return strValOf(str, true);
}

const char *Jnicom::strValOf(std::string str, bool isCopy) {
    const char *retChar = nullptr;
    if (isCopy) {
        char temp[str.length() + 1];
        str.copy(temp, str.length(), 0);
        temp[str.length()] = '\0';
        retChar = temp;
    } else {
        retChar = str.data();
    }
    return retChar;
}

std::string Jnicom::strValOf(jstring str) {
    return strValOf(str, true);
}

std::string Jnicom::strValOf(jstring str, bool isCopy) {
    jboolean jisCopy = isCopy ? JNI_TRUE : JNI_FALSE;
    const char *c_javaName = env->GetStringUTFChars(str, &jisCopy);  //转换为 char *类型,第二个参数表示是否copy
    std::string str_name = c_javaName;
    return str_name;
}

jstring Jnicom::jstrValOf(std::string str) {
    return env->NewStringUTF(str.c_str());
}

int *Jnicom::jintValOf(jintArray intArr) {
    int lenght = env->GetArrayLength(intArr);
    int *cnumArr = env->GetIntArrayElements(intArr, 0);
    return cnumArr;
}

jbyteArray Jnicom::jbyteValOf(const char *charArr, int length) {
    jbyte *ret = (jbyte *) calloc(sizeof(jbyte), length);
    for (int i = 0; i <= length; i++) {
        ret[i] = (jbyte) charArr[i];
    }
    jbyteArray arrRet = env->NewByteArray(length);
    env->SetByteArrayRegion(arrRet, 0, length, ret);
    delete(ret);
    return arrRet;
}

jbyteArray Jnicom::jbyteValOf(std::string str) {
    return jbyteValOf(strValOf(str), str.length());
}

jcharArray Jnicom::jcharValOf(const char *charArr, int length) {

    jchar *j_version = (jchar *) calloc(sizeof(jchar), length);
    for (int i = 0; i <= length; i++) {
        j_version[i] = (jchar) charArr[i];
    }
    jcharArray arrRet = env->NewCharArray(length);
    env->SetCharArrayRegion(arrRet, 0, length, j_version);
    delete(j_version);
    return arrRet;
}

int Jnicom::handleJNILoad(JavaVM *vm, void *reserved, std::string myClassName,
                          const JNINativeMethod* methods,int methodSize) {
    JNIEnv *env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    jclass myClass = env->FindClass(myClassName.data());
    if (myClass == NULL) {
        printf("cannot get class:%s\n", myClassName.data());
        return -1;
    }
    if ((env)->RegisterNatives(myClass, methods,methodSize
                               ) < 0) {
        printf("register native method failed!\n");
        return -1;
    }
    this->env = env;
    LOGD("--------JNI_OnLoad-----");
    return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}


