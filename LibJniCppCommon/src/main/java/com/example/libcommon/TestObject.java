package com.example.libcommon;

import android.util.Log;

/**
 * Created by yuhanxun
 * 2018/8/21
 * description:
 */
public class TestObject {
    public int i = 0;
    public String j;

    public TestObject() {
    }

    public TestObject(int i, String j) {
        this.i = i;
        this.j = j;
    }

    public void doST(String str, int data) {
        Log.d("_xunxun", "str:" + str + " data:" + data);
    }
}
