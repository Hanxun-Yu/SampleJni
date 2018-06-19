//
// Created by yuhanxun on 2018/6/15.
//

#include "main.h"
#include <iostream>

extern "C" {
Jnicom *jnicom;
JNIEXPORT void JNICALL testJnicom(JNIEnv *env, jobject obj,jstring str,jintArray jintArray) {
    LOGE("--------std::string strValOf(jstring str)-----");
    std::string cstring = jnicom->strValOf(str);
    LOGE("--------ret:%s-----",cstring.data());

    LOGE("--------std::string strValOf(jstring str,bool isCopy)-----");
    cstring = jnicom->strValOf(str,true);
    LOGE("---true-----ret:%s-----",cstring.data());

    LOGE("--------int* jintValOf(jintArray intArr)-----");
    int* cintArr = jnicom->jintValOf(jintArray);
    for(int i=0;i<env->GetArrayLength(jintArray);i++) {
        LOGE("ret index:%d val:%d",i,cintArr[i]);
    }
    LOGE("--------const char* strValOf(std::string str)-----");
    const char *charp = jnicom->strValOf(cstring);
    LOGE("ret:%s",charp);

    LOGE("--------const char* strValOf(std::string str,bool isCopy)-----");
    const char *charp2 = jnicom->strValOf(cstring,true);

    LOGE("ret:%s",charp2);
}
JNIEXPORT void JNICALL testjstrValOf(JNIEnv *env, jobject obj) {
}
JNIEXPORT void JNICALL testjcharValOf(JNIEnv *env, jobject obj) {
}
JNIEXPORT void JNICALL testjbyteValOf(JNIEnv *env, jobject obj) {
}

JNINativeMethod nativeMethod[] = {
        {"testJnicom",     "(Ljava/lang/String;[I)V", (void *) testJnicom},
        {"testjstrValOf",  "()Ljava/lang/String;", (void *) testjstrValOf},
        {"testjcharValOf", "()[C", (void *) testjcharValOf},
        {"testjbyteValOf", "()[B", (void *) testjbyteValOf}

};

std::string myClassName = "com/example/libcommon/TestJnicom";
jclass myClass;

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    myClass = env->FindClass(myClassName.data());
    if (myClass == NULL) {
        printf("cannot get class:%s\n", myClassName.data());
        return -1;
    }
    if ((env)->RegisterNatives(myClass, nativeMethod,
                               sizeof(nativeMethod) / sizeof(nativeMethod[0])) < 0) {
        printf("register native method failed!\n");
        return -1;
    }
    LOGE("--------JNI_OnLoad-----");
    printf("--------JNI_OnLoad-----");
    jnicom= new Jnicom(env);
    return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}
}