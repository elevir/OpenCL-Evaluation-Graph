package com.clgraph;

import java.util.ArrayList;

public class Data {

    private long dataPtr;

    static {
        System.loadLibrary("OpenCLEvaluationGraphJava");
    }

    public Data() {
        dataPtr = init();
    }

    public Data(float tensor[], long shape[]) {
        dataPtr = init();
        upload(tensor, shape);
    }

    public boolean upload(float tensor[], long shape[]) {
        return upload(dataPtr, tensor, shape);
    }

    public float[] getData() {
        return getData(dataPtr);
    }

    public long[] getShape() {
        return getShape(dataPtr);
    }

    public boolean reshape(long[] shape) {
        return reshape(dataPtr, shape);
    }

    public String toString() {
        return print(dataPtr);
    }

    private native long init();

    private native boolean upload(long ptr, float tensor[], long shape[]);

    private native float[] getData(long ptr);
    private native long[] getShape(long ptr);

    private native boolean reshape(long ptr, long[] shape);

    private native String print(long ptr);
};