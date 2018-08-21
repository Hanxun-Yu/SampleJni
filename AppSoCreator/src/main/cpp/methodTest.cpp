#include <jni.h>
#include <string>
#include <cstdlib>
#include "my-log.h"
#include "ExternalCTest.h"

extern "C" {
#include "sqlite/sqlite3.h"
}
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

char *myStrCat(char *strArr[], int num);


extern "C" {


static jstring native_method_test1(JNIEnv *env, jobject obj) {
    string ret = "hehe";
    LOGE("native_method_test1:%s", ret.c_str());
    return fromCString(env, ret);
}

static jstring native_method_test2(JNIEnv *env, jclass clazz, jstring str) {
    string ret = fromJString(env, str);
    LOGE("native_method_test2:%s", ret.c_str());
    return fromCString(env, ret);
}

static jint native_method_test3(JNIEnv *env, jobject obj, jint num) {
    int ret = num + 1;
    LOGE("native_method_test3:%d", ret);
    return ret;
}
static jlong native_method_test4(JNIEnv *env, jobject obj, jlong num) {
    long ret = num + 1;
    LOGE("native_method_test4:%ld", ret);
    return ret;
}
static jdouble native_method_test5(JNIEnv *env, jobject obj, jdouble num) {
    double ret = num + 2;
    LOGE("native_method_test5:%f", ret);
    return ret;
}

static jfloat native_method_test6(JNIEnv *env, jobject obj, jfloat num) {
    float ret = num + 3;
    LOGE("native_method_test6:%f", ret);
    return ret;
}
static void native_method_test7(JNIEnv *env, jobject obj, jstring str, jint num) {
    LOGE("native_method_test7 str:%s", fromJString(env, str).c_str());
    LOGE("native_method_test7 num:%d", num);
}
static void native_method_test8(JNIEnv *env, jobject obj, jstring str, jintArray numArr) {
    int lenght = env->GetArrayLength(numArr);
    LOGE("native_method_test8 numArr.length:%d", lenght);
    int *cnumArr = env->GetIntArrayElements(numArr, 0);
    for (int i = 0; i < lenght; i++) {
        LOGE("native_method_test8 numArr[%d]:%d", i, cnumArr[i]);
    }
    LOGE("native_method_test8 str:%s", fromJString(env, str).c_str());
}

static jobjectArray native_method_test9(JNIEnv *env, jobject obj) {
    //findclass 不需要打L和分号
    jclass jstringClazz = env->FindClass("java/lang/String");

    jobjectArray ret = env->NewObjectArray(5, jstringClazz, NULL);

    env->SetObjectArrayElement(ret, 0, env->NewStringUTF("a"));
    env->SetObjectArrayElement(ret, 1, env->NewStringUTF("b"));
    env->SetObjectArrayElement(ret, 2, env->NewStringUTF("c"));
    env->SetObjectArrayElement(ret, 3, env->NewStringUTF("d"));
    env->SetObjectArrayElement(ret, 4, env->NewStringUTF("e"));
    return ret;
//    LOGE("native_method_test7 str:%s", fromJString(env, str).c_str());
}

static jobject native_method_test11(JNIEnv *env, jobject obj, jobject internalObj) {
    //findclass 不需要打L和分号
    jclass internalObjClass = env->GetObjectClass(internalObj);
    //获取object内数据
    jfieldID strFid = env->GetFieldID(internalObjClass, "str", "Ljava/lang/String;");
    jfieldID numFid = env->GetFieldID(internalObjClass, "num", "I");
    jstring strObj = (jstring) env->GetObjectField(internalObj, strFid);
    jint intNum = env->GetIntField(internalObj, numFid);
    LOGE("native_method_test11 str:%s num:%d", fromJString(env, strObj).c_str(), intNum);

    //返回数据
    //构造方法
    //获取方法 id
    jmethodID constructorMid = env->GetMethodID(internalObjClass, "<init>",
                                                "(Ljava/lang/String;I)V");
    jobject ret = env->NewObject(internalObjClass, constructorMid, env->NewStringUTF("tarStr"), 1);

    //手动设置成员变量
//    env->SetObjectField(ret,strFid,env->NewStringUTF("a"));
//    env->SetIntField(ret,numFid,2);
    return ret;
//    LOGE("native_method_test7 str:%s", fromJString(env, str).c_str());
}

jboolean native_sqlite3_open(JNIEnv *env, jobject obj, jstring path) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string cpath = fromJString(env, path);
    rc = sqlite3_open(cpath.c_str(), &db);

    jboolean ret;
    if (rc) {
        LOGE("Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        LOGE("Opened database successfully\n");
    }
    ret = rc;
    LOGE("native_sqlite3_open :rc:%d", rc);
    LOGE("native_sqlite3_open :ret:%d", ret);
    sqlite3_close(db);
    return ret;
}
jboolean native_method_test100(JNIEnv *env, jobject obj, jbyteArray bytes, jint i) {
    jboolean ret;
    return ret;
}
void native_method_testCallback(JNIEnv *env, jobject obj) {
    LOGE("native_method_testCallback");
    jclass clazz = env->GetObjectClass(obj);
    jmethodID dataCallbackMID = env->GetMethodID(clazz, "nativeCallback", "([BIIZII)V");
    jbyteArray jarray = env->NewByteArray(10);
    env->CallVoidMethod(obj, dataCallbackMID, jarray, 0, 0, false, 0, 0);
}

JNINativeMethod nativeMethod[] =
        {{"method_test1",        "()Ljava/lang/String;",                   (void *) native_method_test1},
         {"method_test100",      "([BI)Z",                                 (void *) native_method_test100},
         {"method_test2",        "(Ljava/lang/String;)Ljava/lang/String;", (void *) native_method_test2},
         {"method_test3",        "(I)I",                                   (void *) native_method_test3},
         {"method_test4",        "(J)J",                                   (void *) native_method_test4},
         {"method_test5",        "(D)D",                                   (void *) native_method_test5},
         {"method_test6",        "(F)F",                                   (void *) native_method_test6},
         {"method_test7",        "(Ljava/lang/String;I)V",                 (void *) native_method_test7},
         {"method_test8",        "(Ljava/lang/String;[I)V",                (void *) native_method_test8},
         {"method_test9",        "()[Ljava/lang/String;",                  (void *) native_method_test9},
//         {"method_test11", "(Lcom/example/androidjnilib/MethodTestJni"
//                                   "$MethodTestInternal;)Lcom/example/androidjnilib/MethodTestJni"
//                                   "$MethodTestInternal;",           (void *) native_method_test11}
         {"method_test11",       "(Lcom/example/xunxun/socreator/MethodTestJni"
                                         "$MethodTestInternal;)Lcom/example/xunxun/socreator/MethodTestJni"
                                         "$MethodTestInternal;",           (void *) native_method_test11},
         {"sqlite3_open",        "(Ljava/lang/String;)Z",                  (void *) native_sqlite3_open},
//         {"method_testCallback", "([BIIZII)V",                                    (void *) native_method_testCallback}
         {"method_testCallback", "()V",                                    (void *) native_method_testCallback}
        };


//static string javaClass = "com/example/androidjnilib/MethodTestJni";
static string javaClass = "com/example/xunxun/socreator/MethodTestJni";

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    LOGE("JNI_OnLoad comming");

    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
//    LOGE("JNI_OnLoad comming2");


    jclass clz = env->FindClass(javaClass.c_str());
//    jclass clz = env->FindClass("com/example/androidjnilib/MethodTestJni");

    env->RegisterNatives(clz, nativeMethod, sizeof(nativeMethod) / sizeof(nativeMethod[0]));

    return JNI_VERSION_1_4;
}


}

string fromJString(JNIEnv *env, jstring jstr) {
    const char *c_javaName = env->GetStringUTFChars(jstr, NULL);  //转换为 char *类型
    string str_name = c_javaName;
    return str_name;
}

jstring fromCString(JNIEnv *env, string cstr) {
    jstring ret = env->NewStringUTF(cstr.c_str());
    return ret;
}

int *fromJInt(JNIEnv *env, jintArray array_) {
    int *c_array;
    int arr_len;
    //1. 获取数组长度
    arr_len = env->GetArrayLength(array_);
    //2. 根据数组长度和数组元素的数据类型申请存放java数组元素的缓冲区
    c_array = (int *) malloc(sizeof(int) * arr_len);
    //3. 初始化缓冲区
    memset(c_array, 0, sizeof(int) * arr_len);
    LOGE("arr_len = %d", arr_len);
    //4. 拷贝Java数组中的所有元素到缓冲区中
    env->GetIntArrayRegion(array_, 0, arr_len, c_array);
    return c_array;
    //5. 释放存储数组元素的缓冲区
//    free(c_array);
}


int callSum(int a, int b) {
    return sum(a, b);
}

int callSub(int a, int b) {
    return sub(a, b);
}

char *myStrCat(char *strArr[], int num) {
    char *ret;
    for (int i = 0; i < num; i++) {
        strcat(ret, strArr[i]);
    }
    return ret;
}
