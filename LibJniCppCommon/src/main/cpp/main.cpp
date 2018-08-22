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
    LOGD("byteArr:%p len:%d", byteArr, byteArrLen);

    for (int32_t i = 0; i < byteArrLen; i++) {
        LOGD("byteArr:%d:%u", i, byteArr[i]);
    }


    free(cstr);
    free(byteArr);
    delete (jnicom2);
}
JNIEXPORT jstring JNICALL getString(JNIEnv *env, jobject obj) {
    Jnicom *jnicom2 = new Jnicom(env);
    jstring ret = jnicom2->string2jstring("hahaha");
    delete (jnicom2);
    return ret;
}
JNIEXPORT jbyteArray JNICALL getByteArr(JNIEnv *env, jobject obj) {
    Jnicom *jnicom2 = new Jnicom(env);

    uint8_t temp[] = {12, 32, 45, 67, 230};
    jbyteArray ret = jnicom2->byteArr2jbyteArr(temp, 5);
    delete (jnicom2);

    return ret;
}
//@formatter:off
JNIEXPORT jobject JNICALL createObject(JNIEnv *env, jobject obj) {
    Jnicom *jni = new Jnicom(env);

    jobject ret = jni->createObject("com/example/libcommon/TestObject",
                                        SIGN(Jint JString, Jvoid), 1, jni->string2jstring("aa"));

    jni->setIntField(ret, "i", 3);
    jni->setStringField(ret, "j", jni->string2jstring(SIGN(JbyteArr JStringArr Jboolean, JObject)));
    std::string myClassName = "com/example/libcommon/TestJnicom";

//    jni->invokeVoidMethod(ret, "doST", SIGNATURE(STRING INT, VOID), jni->string2jstring("sss"), 5);
    delete (jni);
    return ret;
}
//@formatter:on
//@formatter:off
JNIEXPORT void JNICALL callbackObject(JNIEnv *env, jobject obj,jobject callbackObj) {
    Jnicom *jni = new Jnicom(env);
    jni->invokeVoidMethod(callbackObj, "doST", SIGN(JString Jint, Jvoid), jni->string2jstring("sss"), 5);
//    jclass myClass = env->GetObjectClass(callbackObj);
//    jmethodID jmethodID1 = env->GetMethodID(myClass, "doST", SIGNATURE(STRING INT, VOID));
//    env->CallVoidMethod(callbackObj,jmethodID1,jni->string2jstring("sss"),1);
    delete (jni);
}
//@formatter:on


//@formatter:off
JNINativeMethod nativeMethod[] =
        {{"testJnicom",   SIGN(JString JbyteArr, Jvoid), (void *) testJnicom},
         {"getString",    SIGN(, JString),          (void *) getString},
         {"getByteArr",   SIGN(, JbyteArr),         (void *) getByteArr},
         {"createObject", SIGN(, JObject),          (void *) createObject},
         {"callbackObject", SIGN(JObject, Jvoid),          (void *) callbackObject},
        };
std::string myClassName = "com/example/libcommon/TestJnicom";
//@formatter:on

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    return Jnicom::handleJNILoad(vm, reserved, myClassName, nativeMethod,
                                 sizeof(nativeMethod) / sizeof(nativeMethod[0]));
}

}