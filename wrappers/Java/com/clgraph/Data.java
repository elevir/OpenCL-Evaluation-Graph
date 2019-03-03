package com.clgraph;

public class Data {

    long dataPtr = 0;

    static {
        System.loadLibrary("OpenCLEvaluationGraphJava");
    }

    Data(long ptr) {
        dataPtr = ptr;
    }

    public Data() {
        dataPtr = init();
    }

    protected void finalize() {
        deInit(dataPtr);
        dataPtr = 0;
    }

    public Data(float[] tensor, long[] shape) {
        dataPtr = init();
        upload(tensor, shape);
    }

    public Data(float[] vector) {
        dataPtr = init();
        long[] shape = {vector.length};
        upload(vector, shape);
    }

    public Data(float scalar) {
        dataPtr = init();
        float[] dt = { scalar };
        long[] shape = { 1 };
        upload(dt, shape);
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
    private native void deInit(long ptr);

    private native boolean upload(long ptr, float tensor[], long shape[]);

    private native float[] getData(long ptr);
    private native long[] getShape(long ptr);

    private native boolean reshape(long ptr, long[] shape);

    private native String print(long ptr);
};