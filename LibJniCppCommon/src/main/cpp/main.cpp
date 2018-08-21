//
// Created by yuhanxun on 2018/6/15.
//

#include "main.h"
#include <iostream>
#include <cstdlib>

extern "C" {


JNIEXPORT void JNICALL testJnicom(JNIEnv *env, jobject obj, jstring str, jbyteArray jbytearr) {
    Jnicom *jnicom2 = new Jnicom(env);
    std::string cppstr = jnicom2->jstring2string(str);
    char *cstr = jnicom2->jstring2char_p(str);
    uint8_t *byteArr = nullptr;
    int32_t byteArrLen;
    jnicom2->jbyteArr2byteArr(jbytearr, byteArr, byteArrLen);

    LOGD("cppstr:%s", cppstr.c_str());
    LOGD("cstr:%s", cstr);
    LOGD("byteArr:%p len:%d", byteArr,byteArrLen);

    for (int32_t i = 0; i < byteArrLen; i++) {
        LOGD("byteArr:%d:%u", i,byteArr[i]);
    }


    free(cstr);
    free(byteArr);
    delete(jnicom2);
}
JNIEXPORT jstring JNICALL getString(JNIEnv *env, jobject obj) {
    Jnicom *jnicom2 = new Jnicom(env);
    jstring ret = jnicom2->string2jstring("hahaha");
    delete(jnicom2);
    return ret;
}
JNIEXPORT jbyteArray JNICALL getByteArr(JNIEnv *env, jobject obj) {

}


JNINativeMethod nativeMethod[] = {
        {"testJnicom", "(Ljava/lang/String;[B)V", (void *) testJnicom},
        {"getString",  "()Ljava/lang/String;",     (void *) getString},
        {"getByteArr", "()[B",                    (void *) getByteArr},
};

std::string myClassName = "com/example/libcommon/TestJnicom";

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    return Jnicom::handleJNILoad(vm, reserved, myClassName, nativeMethod, sizeof(nativeMethod) /
                                                                          sizeof(nativeMethod[0]));
}

}