//
// Created by yuhanxun on 2019/3/4.
//


#include "JniHelper.h"


extern "C" {
#define MAX_BUFFER_SIZE    (1024 * 1024)

#include "https.h"
JNIEXPORT jstring JNICALL getAuth(JNIEnv *env, jobject obj) {
    LOGE("getAuth");
    char *resp = static_cast<char *>(malloc(MAX_BUFFER_SIZE));
    const char *host = "api-cn.faceplusplus.com";
    uint16_t port = 443;
    const char *path = "/sdk/v3/auth";
    const char *body = "a=dw";
    int n = https_send_request(POST, host, port, path, body, resp,
                               MAX_BUFFER_SIZE);



    LOGE("n=%d ,%s\n", n, resp);
    int i=0;
    int lastEnter = 0;
    for(i=0;i<n;i++)
    {
        if(i+1 <=n && resp[i]=='\r' && resp[i+1]=='\n') {
            lastEnter = i+2;
        }
    }
    LOGE("_xunxun lastEnter=%d\n",lastEnter);
    LOGE("_xunxun resp=%s len=%d\n",resp+lastEnter,strlen(resp+lastEnter));


    return NULL;
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

}