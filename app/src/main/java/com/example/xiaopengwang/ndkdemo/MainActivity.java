package com.example.xiaopengwang.ndkdemo;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("one-lib");
        System.loadLibrary("two-lib");
    }
    Button invokec,invokec1;
    Context mContext;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mContext =this;
        invokec = (Button) findViewById(R.id.invokec);
        invokec1 = (Button) findViewById(R.id.invokec1);
        invokec.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(mContext,stringFromJNI2(),Toast.LENGTH_LONG).show();
            }
        });
        invokec1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(mContext,add(10,10)+"",Toast.LENGTH_LONG).show();
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI2();
    public native int add(int x, int y);
    public native String helloC(String c);
}
