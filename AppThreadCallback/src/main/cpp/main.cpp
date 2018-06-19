//
// Created by yuhanxun on 2018/6/19.
//

#include "main.h"

ThreadHandler *threadHandler;
Jnicom *jnicom = new Jnicom();

class MyCallback : public ICallback {
public:
    JNIEnv *env;
    jobject obj;
    jmethodID strTest_id;

    MyCallback(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = obj;
        jclass cls = env->GetObjectClass(this->obj);
        if (cls != NULL) {
            strTest_id = env->GetMethodID(cls, "callbackFromC", "(Ljava/lang/String;)V");
        }
    }

    void onCallback(std::string fileName, bool bOK) override {
        LOGE("c++callback fileName:%s bOK:%d", fileName.data(), bOK);
        if (strTest_id != NULL) {
            env->CallVoidMethod(this->obj, strTest_id, jnicom->jstrValOf(fileName));
        }
    }
};


extern "C" {

JNIEXPORT void JNICALL init(JNIEnv *env, jobject obj) {
    LOGE("init");
    threadHandler = new ThreadHandler();
}
JNIEXPORT void JNICALL start(JNIEnv *env, jobject obj) {
    LOGE("start");
    ICallback *callback = new MyCallback(env, obj);
    threadHandler->setCallback(callback);
    threadHandler->start();
}
JNIEXPORT void JNICALL stop(JNIEnv *env, jobject obj) {
    LOGE("stop");

    threadHandler->stop();
}

}

JNINativeMethod nativeMethod[] = {
        {"init",  "()V", (void *) init},
        {"start", "()V", (void *) start},
        {"stop",  "()V", (void *) stop}
};


std::string myClassName = "com/example/appthreadcallback/MainActivity";

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {

    return jnicom->handleJNILoad(vm, reserved, myClassName,
                                 nativeMethod, sizeof(nativeMethod) / sizeof(nativeMethod[0]));
}