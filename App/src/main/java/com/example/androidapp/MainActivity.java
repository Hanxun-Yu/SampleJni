package com.example.androidapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.libcommon.TestJnicom;


//import com.example.androidjnilib.MethodTestJni;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        MethodTestJni.loadLibrariesOnce(null);
//        MethodTestJni methodTestJni = new MethodTestJni(this);

//        DependExternalSoJni dependExternalSoJni = new DependExternalSoJni();

//        TextView textView = findViewById(R.id.text);
//        textView.setText(dependExternalSoJni.method_test1());
        final TestJnicom jnicom = new TestJnicom();
        new Thread(new Runnable() {
            @Override
            public void run() {
                for(long i=0;i<100000000;i++) {
                    Log.d("_xunxun","i:"+i);
//                    jnicom.testJnicom("dawd", new byte[]{56, 78, 32});
                    Log.d("_xunxun","getString:"+jnicom.getString());
                }
            }
        }).start();

    }
}
