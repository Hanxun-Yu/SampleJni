//
// Created by yuhanxun on 2018/6/15.
//

#ifndef SAMPLEJNI_JNICOM_H
#define SAMPLEJNI_JNICOM_H

#include <jni.h>
#include <string>
#include "logcat.h"
class Jnicom {
public:
    /**
     * In jni file, you can call Jnicom* jnicom = new Jnicom() in globle region.
     * and call handleJNILoad() in JNI_OnLoad() ,then the *env will be inited automatically
     */
    Jnicom();

    /**
     * If not in jni file or in any function internal local region ,you must init *env manually
     * you ca
     * @param env
     */
    Jnicom(JNIEnv * env);

    /**
     * call in JNI_OnLoad()
     * @param vm
     * @param reserved unused
     * @param myClassName eg. "com/example/libcommon/TestJnicom"
     * @param methods eg. JNINativeMethod nativeMethod[]
     * @param methodSize eg. methodSize = sizeof(nativeMethod)/sizeof(nativeMethod[0])
     * @return
     */
    static int handleJNILoad(JavaVM *vm, void *reserved,std::string myClassName,const JNINativeMethod* methods,int methodSize);

    /**
     * jstring -> string
     * internal <> jstring2char_p()
     * @param jstr
     * @return
     */
    std::string jstring2string(jstring jstr);

    /**
     * jstring -> char*
     * This will malloc a new string,
     * please free it after use.
     * @param jstr
     * @return
     */
    char* jstring2char_p(jstring jstr);

    /**
     * string -> jstring
     * internal <> char_p2jstring()
     * @param str
     * @return
     */
    jstring string2jstring(std::string str);

    /**
     * By default, this use utf-8(env->NewStringUTF) encoder to convert string
     * because String in Java must has Encoder
     * @param char_p
     * @return
     */
    jstring char_p2jstring(char* char_p);

    /**
     * If @param byteArr is NULL,this will malloc automatically according to @param len
     * then please free it after use
     * @param jbyteArr :src
     * @param byteArr :target
     * @param len :The length of byteArr
     */
    void jbyteArr2byteArr(jbyteArray jbyteArr,uint8_t* &byteArr,int32_t &len);


    /**
     * uint8_t* -> jbyteArray
     * @param byteArr
     * @param len
     * @return
     */
    jbyteArray byteArr2jbyteArr(uint8_t* byteArr,int32_t len);

    /**
     * remember free dst* after use
     * @param src
     */
    char* strcpyWrap(char* src);

private:
    JNIEnv *env;
};


#endif //SAMPLEJNI_JNICOM_H
