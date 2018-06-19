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

    public native void  testJnicom(String str,int[] intArr);
    public native String testjstrValOf();
    public native char[] testjcharValOf();
    public native byte[] testjbyteValOf();
}
