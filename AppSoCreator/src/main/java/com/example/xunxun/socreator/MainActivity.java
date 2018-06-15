package com.example.xunxun.socreator;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

public class MainActivity extends Activity {

    String TAG = "MainActivity_xunxun";
    MethodTestJni methodTestJni;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        methodTestJni = new MethodTestJni(this);
        MethodTestJni.loadLibrariesOnce(null);

//        NativeLibJni nativeLibJni = new NativeLibJni();
        // Example of a call to a native method
//        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(nativeLibJni.stringFromJNI());

//        nativeLibJni.stringFromJNI();
//        nativeLibJni.stringFromJNI2();
//        nativeLibJni.nativeDynamicLog();

//        methodTestJni.method_test1();
//        MethodTestJni.method_test2("baibai");
//        methodTestJni.method_test3(4);
//        methodTestJni.method_test8("haha",new int[]{6,7,8,9,0});
//        String[] ret = methodTestJni.method_test9();
//        Log.e(TAG, Arrays.toString(ret));
//        MethodTestJni.MethodTestInternal mti =
//                methodTestJni.method_test11(new MethodTestJni.MethodTestInternal("srcStr",0));
//        Log.e(TAG, "mti:"+mti.toString());
//        Log.e(TAG, "sqlite3_open :"+methodTestJni.sqlite3_open(getObbDir().getPath()+"/sqlite.db"));
        methodTestJni.method_testCallback();
    }


}
