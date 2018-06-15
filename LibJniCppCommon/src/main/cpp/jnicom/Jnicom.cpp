//
// Created by yuhanxun on 2018/6/15.
//

#include <cstdlib>
#include "Jnicom.h"

Jnicom::Jnicom(JNIEnv *env) {
    this->env = env;
}

const char *Jnicom::strValOf(std::string str) {
    return strValOf(str, false);
}

const char *Jnicom::strValOf(std::string str, bool isCopy) {
    const char *retChar = nullptr;
    if (isCopy) {
        char temp[str.length() + 1];
        str.copy(temp, str.length() + 1, 0);
        retChar = temp;
    } else {
        retChar = str.data();
    }
    return retChar;
}

std::string Jnicom::strValOf(char *p) {
    return p;
}

std::string Jnicom::strValOf(jstring str) {
    return strValOf(str, false);
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
    return arrRet;
}

jbyteArray Jnicom::jbyteValOf(std::string str) {
    return jbyteValOf(strValOf(str), sizeof(str));
}


