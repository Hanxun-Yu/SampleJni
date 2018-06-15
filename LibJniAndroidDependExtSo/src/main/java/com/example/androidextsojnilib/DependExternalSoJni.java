package com.example.androidextsojnilib;

/**
 * Created by xunxun on 2018/3/8.
 */

public class DependExternalSoJni {

    static {

        System.loadLibrary("dependExternalSo");
        System.loadLibrary("methodTest");
    }



    public native String method_test1();
}
