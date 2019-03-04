//
// Created by yuhanxun on 2019/3/4.
//


#include "JniHelper.h"
#include "https.h"

#define MAX_BUFFER_SIZE    (1024 * 1024)
extern "C" {
JNIEXPORT jstring JNICALL getAuth(JNIEnv *env, jobject obj) {
    LOGE("getAuth");
    char *resp = static_cast<char *>(malloc(MAX_BUFFER_SIZE));
    const char *host = "api-cn.faceplusplus.com";
    uint16_t port = 443;
    const char *path = "/sdk/v3/auth";
    const char *body = "";
    int n = https_send_request(POST, host, port, path, body, resp,
                               MAX_BUFFER_SIZE);
    LOGE("n=%d\n,%s\n", n, resp);
    return NULL;
}
}

JNINativeMethod nativeMethod[] = {
        {"getAuth", SIGN(, JString), (void *) getAuth},

};
std::string myClassName = "com/example/xunxun/socreator/HttpsJni";

JNIEXPORT jint

JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {

    return JniHelper::handleJNILoad(vm, reserved, myClassName,
                                    nativeMethod, sizeof(nativeMethod) / sizeof(nativeMethod[0]));
}