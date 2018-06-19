package com.example.androidapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;


//import com.example.androidjnilib.MethodTestJni;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        MethodTestJni.loadLibrariesOnce(null);
//        MethodTestJni methodTestJni = new MethodTestJni(this);

//        DependExternalSoJni dependExternalSoJni = new DependExternalSoJni();

        TextView textView = findViewById(R.id.text);
//        textView.setText(dependExternalSoJni.method_test1());
    }
}
