package com.example.s_jobi605.gg;

import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {
    private Handler handler = new Handler();
    private TextView timerText;
    private SimpleDateFormat dataFormat =
            new SimpleDateFormat("mm:ss.S", Locale.US);

    private int count, period;
    private int lockTime = 10;

    private Runnable runnable = new Runnable() {
        @Override
        public void run() {

            // タイマー処理
            timerText.setText(dataFormat.
                    format(count*period));
            int timeCount = count*period;
            handler.postDelayed(this, period);

            if(timeCount < lockTime * period * 10)
            {
                count ++;
            }
        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        count = 0;
        period = 100;

        timerText = findViewById(R.id.timer);
        timerText.setText(dataFormat.format(0));

        Button startButton = findViewById(R.id.start_button);
        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handler.post(runnable);
            }
        });

        // タイマー終了
        Button stopButton = findViewById(R.id.stop_button);
        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                StopTimer();
            }
        });
    }
    private void StopTimer(){
        handler.removeCallbacks(runnable);
        timerText.setText(dataFormat.format(0));
        count = 0;
    }
}
