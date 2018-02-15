package com.example.project.game;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    View mView;

    /*
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mView = new View(getApplication());
        setContentView(mView);

        /*
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        */
    }

    @Override
    protected void onPause(){
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume(){
        super.onResume();
        mView.onResume();
    }
}
