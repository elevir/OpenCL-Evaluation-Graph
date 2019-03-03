package com.clgraph;

import java.util.ArrayList;

public class Device {

    private long devicePtr;

    static {
        System.loadLibrary("OpenCLEvaluationGraphJava");
    }

    public Device() {
        devicePtr = init();
    }

    public String toString() {
        return print(devicePtr);
    }

    private native long init();

    private native String print(long ptr);
};