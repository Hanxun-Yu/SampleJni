package com.example.libcommon;

/**
 * Created by yuhanxun
 * 2018/6/19
 */
public class TestJnicom {
    static {
        System.loadLibrary("jnicom");
        System.loadLibrary("jnicomTest");
    }

    public native void  testJnicom(String str,byte[] arr);
    public native String getString();
    public native byte[] getByteArr();
    public native Object createObject();
}
