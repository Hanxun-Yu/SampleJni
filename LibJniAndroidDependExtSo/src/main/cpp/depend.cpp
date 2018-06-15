#include "depend.h"
#include <jni.h>
#include <string>
#include "my-log.h"
#include <sstream>

extern int sum(int a, int b);
using namespace std;

//#define LOG_TAG "main.cpp"


//JNIEXPORT jstring JNICALL Java_com_example_xunxun_testjni_MainActivity_stringFromJNI(
//        JNIEnv *env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
//}

static string fromJString(JNIEnv *env, jstring jstr);

static jstring fromCString(JNIEnv *env, string cstr);



extern "C" {


static jstring native_method_test1(JNIEnv *env, jobject obj) {
    int sumRes = sum(1,2);
//    int sumRes = 0;

    LOGE("native_method_test1 sumRes:%d",sumRes);
    string ret = "hehe";
    stringstream ss;
    ss << ret << sumRes;
    LOGE("native_method_test1:%s", ss.str().c_str());
    return fromCString(env, ss.str().c_str());
}




JNINativeMethod nativeMethod[] =
        {{"method_test1",  "()Ljava/lang/String;",(void *) native_method_test1},
        };



JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    LOGE("JNI_OnLoad comming");

    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
//    LOGE("JNI_OnLoad comming2");


    jclass clz = env->FindClass("com/example/androidextsojnilib/DependExternalSoJni");
//    jclass clz = env->FindClass("com/example/androidjnilib/MethodTestJni");

    env->RegisterNatives(clz, nativeMethod, sizeof(nativeMethod) / sizeof(nativeMethod[0]));

    return JNI_VERSION_1_4;
}


}


static string fromJString(JNIEnv *env, jstring jstr) {
    const char *c_javaName = env->GetStringUTFChars(jstr, NULL);  //转换为 char *类型
    string str_name = c_javaName;
    return str_name;
}

static jstring fromCString(JNIEnv *env, string cstr) {
    return env->NewStringUTF(cstr.c_str());
}