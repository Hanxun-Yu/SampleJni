//
// Created by yuhanxun on 2018/6/15.
//

#include "main.h"
#include <iostream>

extern "C" {
Jnicom *jnicom = new Jnicom();
JNIEXPORT void JNICALL testJnicom(JNIEnv *env, jobject obj, jstring str, jintArray jintArray) {
    LOGE("--------std::string strValOf(jstring str)-----");
    std::string cstring = jnicom->strValOf(str);
    LOGE("--------ret:%s-----", cstring.data());

    LOGE("--------std::string strValOf(jstring str,bool isCopy)-----");
    cstring = jnicom->strValOf(str, true);
    LOGE("---true-----ret:%s-----", cstring.data());

    LOGE("--------int* jintValOf(jintArray intArr)-----");
    int *cintArr = jnicom->jintValOf(jintArray);
    for (int i = 0; i < env->GetArrayLength(jintArray); i++) {
        LOGE("ret index:%d val:%d", i, cintArr[i]);
    }
    LOGE("--------const char* strValOf(std::string str)-----");
    const char *charp = jnicom->strValOf(cstring);
    LOGE("ret:%s", charp);

    LOGE("--------const char* strValOf(std::string str,bool isCopy)-----");
    const char *charp2 = jnicom->strValOf(cstring, true);

    LOGE("ret:%s", charp2);
}
JNIEXPORT jstring JNICALL testjstrValOf(JNIEnv *env, jobject obj) {
    return jnicom->jstrValOf("hahaha");

}
JNIEXPORT jcharArray JNICALL testjcharValOf(JNIEnv *env, jobject obj) {
    const char charArr[] = "charArrTest";
    return jnicom->jcharValOf(charArr, strlen(charArr));
}
JNIEXPORT jbyteArray JNICALL testjbyteValOf(JNIEnv *env, jobject obj) {
    return jnicom->jbyteValOf("hahaha");
}

JNINativeMethod nativeMethod[] = {
        {"testJnicom",     "(Ljava/lang/String;[I)V", (void *) testJnicom},
        {"testjstrValOf",  "()Ljava/lang/String;",    (void *) testjstrValOf},
        {"testjcharValOf", "()[C",                    (void *) testjcharValOf},
        {"testjbyteValOf", "()[B",                    (void *) testjbyteValOf}

};

std::string myClassName = "com/example/libcommon/TestJnicom";

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    return jnicom->handleJNILoad(vm, reserved, myClassName, nativeMethod, sizeof(nativeMethod) /
                                                                          sizeof(nativeMethod[0]));
}
}