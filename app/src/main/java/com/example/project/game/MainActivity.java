package com.example.project.game;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

    View mView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mView = new View(getApplication(), this);
        setContentView(mView);
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
