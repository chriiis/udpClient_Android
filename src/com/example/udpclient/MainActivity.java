
package com.example.udpclient;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {
    private EditText mIpEditor;
    private EditText mPortEditor;
    private TextView mIllustrateTextView;
    private Button mInitBtn;
    private Button mSendBtn;
    private Button mPauseBtn;
    
    private String mIpAddr;
    private String mPort;
    private int port;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();     
    }

    private void initView(){
        mIllustrateTextView = (TextView) findViewById(R.id.illustrate);
        mIpEditor = (EditText) findViewById(R.id.ip);
        mPortEditor = (EditText) findViewById(R.id.port);
        mSendBtn = (Button) findViewById(R.id.send);
        mPauseBtn = (Button) findViewById(R.id.pause_send);
        mInitBtn = (Button) findViewById(R.id.init);
        
        mInitBtn.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                mIpAddr = mIpEditor.getText()+"";
                mPort = mPortEditor.getText()+"";
                port = Integer.parseInt(mPort);
                
                int sock = Interface.nativeCreateUdpClient(mIpAddr, port);
                if (sock == -1000){
                    mIllustrateTextView.setText("Udp客户端未初始化...");
                }
                else{
                    mIllustrateTextView.setText("初始化成功，当前Socket=" + sock);
                }
                
                
            }
        });
        
        mSendBtn.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                Interface.nativeStartSendTimer();
            }
        });
        
        mPauseBtn.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                Interface.nativeStopTimer();
            }
        });
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
