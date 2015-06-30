package com.example.udpclient;

import java.nio.ByteBuffer;

public class Interface
{
    public static native int nativeCreateUdpClient(String ip, int port);                       
    public static native int nativeDeleteUdpClient();                                                          
    public static native void nativeStartSendTimer();
    public static native void nativeStopTimer();
    
    private static final String NativeLib = "UdpClient";
    static {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary(NativeLib);
    }
}

