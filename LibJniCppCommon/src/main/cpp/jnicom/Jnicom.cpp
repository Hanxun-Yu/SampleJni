//
// Created by yuhanxun on 2018/6/15.
//


#include "Jnicom.h"

//Jnicom::Jnicom() {
//}

Jnicom::Jnicom(JNIEnv *env) {
    this->env = env;
}

std::string Jnicom::jstring2string(jstring jstr) {
    /**
     *  dont do this like : return jstring2char_p(jstr);
     *  because jstring2char_p(jstr) will malloc char*,  return immediately will keep char* in memory
     *
     * when char* assign to string, C++ will copy data from char* to string
     * after the above, just free char* now and return string
     */
    char *temp = jstring2char_p(jstr);
    std::string ret = temp;
    free(temp);
    return ret;
}


char *Jnicom::jstring2char_p(jstring jstr) {
    const char *str_src = env->GetStringUTFChars(jstr, NULL);
    char *ret = strcpyWrap(const_cast<char *>(str_src));
    env->ReleaseStringUTFChars(jstr, str_src);
    return ret;
}

jstring Jnicom::string2jstring(std::string str) {
    return char_p2jstring(const_cast<char *>(str.c_str()));
}

jstring Jnicom::char_p2jstring(char *char_p) {
    jstring ret = env->NewStringUTF(char_p);
    return ret;
}

void Jnicom::jbyteArr2byteArr(jbyteArray jbyteArr, uint8_t *&byteArr, int32_t &len) {
    jbyte *jbyte1 = env->GetByteArrayElements(jbyteArr, NULL);
    len = env->GetArrayLength(jbyteArr);
    if (!byteArr) {
        byteArr = (uint8_t *) malloc(len);
    }
    memset(byteArr, 0, len);
    memcpy(byteArr, jbyte1, len);
    env->ReleaseByteArrayElements(jbyteArr, jbyte1, 0);//最后参数0,会释放jbyte1 所指向的内存的
}

jbyteArray Jnicom::byteArr2jbyteArr(uint8_t *byteArr, int32_t len) {
    jbyte *temp = (jbyte *) malloc(sizeof(jbyte) * len);
    for (int i = 0; i <= len; i++) {
        temp[i] = byteArr[i];
    }

    jbyteArray ret = env->NewByteArray(len);
    env->SetByteArrayRegion(ret, 0, len, temp);

    free(temp);
    return ret;
}


char *Jnicom::strcpyWrap(char *src) {
    char *dst = (char *) malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dst, src);
    return dst;
}

jobject Jnicom::createObject(char *classpath, char *constructorSignature, ...) {
    jclass myClass = env->FindClass(classpath);
    jmethodID constructorMid = env->GetMethodID(myClass, "<init>",
                                                constructorSignature);
    va_list args;
    va_start(args, constructorMid);
    jobject ret = env->functions->NewObjectV(env, myClass, constructorMid, args);
    va_end(args);

    env->DeleteLocalRef(myClass);
    return ret;
}

void Jnicom::invokeVoidMethod(jobject obj, char *methodName, char *methodSignature, ...) {
    jclass myClass = env->GetObjectClass(obj);
    jmethodID jmethodID1 = env->GetMethodID(myClass, methodName,
                                                methodSignature);
    va_list args;
    va_start(args, jmethodID1);
    env->functions->CallVoidMethod(env, myClass, jmethodID1, args);
    va_end(args);
    env->DeleteLocalRef(myClass);
}

void Jnicom::invokeVoidStaticMethod(char *classpath, char *methodName, char *methodSignature, ...) {
    jclass myClass = env->FindClass(classpath);
    jmethodID jmethodID1 = env->GetStaticMethodID(myClass, methodName,
                                            methodSignature);
    va_list args;
    va_start(args, jmethodID1);
    env->functions->CallStaticVoidMethod(env, myClass, jmethodID1, args);
    va_end(args);
    env->DeleteLocalRef(myClass);
}

jfieldID Jnicom::getFieldID(jobject obj, const char *fieldName, const char *typeSignature) {
    jclass internalObjClass = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(internalObjClass, fieldName, typeSignature);
    env->DeleteLocalRef(internalObjClass);
    return fid;
}

jint Jnicom::getIntField(jobject obj, const char *fieldName) {
    jfieldID intFid = getFieldID(obj, fieldName, SIGN_INT);
    jint intNum = env->GetIntField(obj, intFid);
    return intNum;
}

jboolean Jnicom::getBooleanField(jobject obj, const char *fieldName) {
    jfieldID fid = getFieldID(obj, fieldName, SIGN_BOOLEAN);
    jboolean jboolean1 = env->GetBooleanField(obj, fid);
    return jboolean1;
}

jstring Jnicom::getStringField(jobject obj, const char *fieldName) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_STRING);
    jobject str = env->GetObjectField(obj, strFid);
    return static_cast<jstring>(str);
}

jlong Jnicom::getLongField(jobject obj, const char *fieldName) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_LONG);
    jlong ret = env->GetLongField(obj, strFid);
    return ret;
}

jfloat Jnicom::getFloatField(jobject obj, const char *fieldName) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_FLOAT);
    jfloat ret = env->GetFloatField(obj, strFid);
    return ret;
}

jdouble Jnicom::getDoubleField(jobject obj, const char *fieldName) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_DOUBLE);
    jdouble ret = env->GetDoubleField(obj, strFid);
    return ret;
}

jbyte Jnicom::getByteField(jobject obj, const char *fieldName) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_BYTE);
    jbyte ret = env->GetByteField(obj, strFid);
    return ret;
}

jchar Jnicom::getCharField(jobject obj, const char *fieldName) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_CHAR);
    jchar ret = env->GetCharField(obj, strFid);
    return ret;
}

jshort Jnicom::getShortField(jobject obj, const char *fieldName) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_SHORT);
    jshort ret = env->GetShortField(obj, strFid);
    return ret;
}

jobject Jnicom::getObjectField(jobject obj, const char *fieldName, const char *classpath) {
    if (!classpath) {
        classpath = SIGN_OBJECT;
    }
    jfieldID strFid = getFieldID(obj, fieldName, classpath);
    jobject ret = env->GetObjectField(obj, strFid);
    return ret;
}

jobject Jnicom::getObjectField(jobject obj, const char *fieldName) {
    return getObjectField(obj, fieldName, NULL);
}

void Jnicom::setIntField(jobject obj, const char *fieldName, jint val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_INT);
    env->SetIntField(obj, strFid, val);
}

void Jnicom::setLongField(jobject obj, const char *fieldName, jlong val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_LONG);
    env->SetLongField(obj, strFid, val);
}

void Jnicom::setFloatField(jobject obj, const char *fieldName, jfloat val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_FLOAT);
    env->SetFloatField(obj, strFid, val);
}

void Jnicom::setDoubleField(jobject obj, const char *fieldName, jdouble val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_DOUBLE);
    env->SetDoubleField(obj, strFid, val);
}

void Jnicom::setBooleanField(jobject obj, const char *fieldName, jboolean val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_BOOLEAN);
    env->SetBooleanField(obj, strFid, val);
}

void Jnicom::setStringField(jobject obj, const char *fieldName, jstring val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_STRING);
    env->SetObjectField(obj, strFid, val);
}

void Jnicom::setByteField(jobject obj, const char *fieldName, jbyte val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_BYTE);
    env->SetByteField(obj, strFid, val);
}

void Jnicom::setCharField(jobject obj, const char *fieldName, jchar val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_CHAR);
    env->SetCharField(obj, strFid, val);
}

void Jnicom::setShortField(jobject obj, const char *fieldName, jshort val) {
    jfieldID strFid = getFieldID(obj, fieldName, SIGN_SHORT);
    env->SetShortField(obj, strFid, val);
}

void Jnicom::setObjectField(jobject obj, const char *fieldName,
                            const char *classpath, jobject val) {
    if (!classpath) {
        classpath = SIGN_OBJECT;
    }
    jfieldID strFid = getFieldID(obj, fieldName, classpath);
    env->SetObjectField(obj, strFid, val);
}

void Jnicom::setObjectField(jobject obj, const char *fieldName, jobject val) {
    setObjectField(obj, fieldName, NULL, val);
}

int Jnicom::handleJNILoad(JavaVM *vm, void *reserved, std::string myClassName,
                          const JNINativeMethod *methods, int methodSize) {
    JNIEnv *env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    jclass myClass = env->FindClass(myClassName.data());
    if (myClass == NULL) {
        printf("cannot get class:%s\n", myClassName.data());
        return -1;
    }
    if ((env)->RegisterNatives(myClass, methods, methodSize
    ) < 0) {
        printf("register native method failed!\n");
        return -1;
    }
    LOGD("--------JNI_OnLoad-----");
    return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}


