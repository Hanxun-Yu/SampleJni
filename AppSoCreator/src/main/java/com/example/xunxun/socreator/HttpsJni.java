package com.example.xunxun.socreator;

/**
 * Created by yuhanxun
 * 2019/3/4
 * description:
 */
public class HttpsJni {
    static {
        System.loadLibrary("https");
    }
    public native String getAuth();
}
