//
// Created by yuhanxun on 2018/6/15.
//

#include <iostream>
#include <cstdlib>
#include <JniHelper.h>

extern "C" {
JniHelper* jnicom;


JNIEXPORT void JNICALL testJnicom(JNIEnv* env, jobject obj, jstring str, jbyteArray jbytearr) {
    std::string cppstr = jnicom->jstring2string(str);
    char* cstr = jnicom->jstring2char_p(str);
    uint8_t* byteArr = nullptr;
    int32_t byteArrLen;
    jnicom->jbyteArr2byteArr(jbytearr, byteArr, byteArrLen);

    LOGD("cppstr:%s", cppstr.c_str());
    LOGD("cstr:%s", cstr);
    LOGD("byteArr:%p len:%d", byteArr, byteArrLen);

    for (int32_t i = 0; i < byteArrLen; i++) {
        LOGD("byteArr:%d:%u", i, byteArr[i]);
    }


    free(cstr);
    free(byteArr);
}
JNIEXPORT jstring JNICALL getString(JNIEnv* env, jobject obj) {
    jstring ret = jnicom->string2jstring("hahaha");
    return ret;
}
JNIEXPORT jbyteArray JNICALL getByteArr(JNIEnv* env, jobject obj) {

    uint8_t temp[] = {12, 32, 45, 67, 230};
    jbyteArray ret = jnicom->byteArr2jbyteArr(temp, 5);

    return ret;
}
//@formatter:off
JNIEXPORT jobject JNICALL createObject(JNIEnv* env, jobject obj) {

//    jobject ret = jni->createObject("com/example/libcommon/TestObject",
//                                        SIGN(Jint JString, Jvoid), 1, jni->string2jstring("aa"));
    jobject ret = jnicom->createObject("com/example/libcommon/TestObject",
                                       SIGN(, Jvoid));

    jnicom->setIntField(ret, "i", 3);
    jnicom->setStringField(ret, "j", jnicom->string2jstring(SIGN(JbyteArr
                                                                         JStringArr
                                                                         Jboolean, JObject)));
    std::string myClassName = "com/example/libcommon/TestJnicom";

//    jni->invokeVoidMethod(ret, "doST", SIGNATURE(STRING INT, VOID), jni->string2jstring("sss"), 5);
    return ret;
}
//@formatter:on
//@formatter:off
JNIEXPORT void JNICALL callbackObject(JNIEnv* env, jobject obj, jobject callbackObj) {
//    JniHelper *jni = new JniHelper(env);
//    jni->invokeVoidMethod(callbackObj, "doST", SIGN(JString Jint, Jvoid), jni->string2jstring("sss"), 5);
//    jclass myClass = env->GetObjectClass(callbackObj);
//    jmethodID jmethodID1 = env->GetMethodID(myClass, "doST", SIGNATURE(STRING INT, VOID));
//    env->CallVoidMethod(callbackObj,jmethodID1,jni->string2jstring("sss"),1);
//    delete (jni);
}
//@formatter:on


//@formatter:off
JNINativeMethod nativeMethod[] =
        {{"testJnicom",     SIGN(JString
                                         JbyteArr, Jvoid), (void*) testJnicom},
         {"getString",      SIGN(, JString),               (void*) getString},
         {"getByteArr",     SIGN(, JbyteArr),              (void*) getByteArr},
         {"createObject",   SIGN(, JObject),               (void*) createObject},
         {"callbackObject", SIGN(JObject, Jvoid),          (void*) callbackObject},
        };
std::string myClassName = "com/example/libcommon/TestJnicom";
//@formatter:on
JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    jnicom = new JniHelper(vm);
    return JniHelper::handleJNILoad(vm, reserved, myClassName, nativeMethod,
                                    sizeof(nativeMethod) / sizeof(nativeMethod[0]));
}

}