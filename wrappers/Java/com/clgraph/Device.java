package com.clgraph;

public class Device {

    public enum Type {
        DEFAULT,
        GPU,
        FPGA,
        CPU,
        NOT_CL_CPU,
        INVALID,
    };

    long devicePtr;

    static {
        System.loadLibrary("OpenCLEvaluationGraphJava");
    }

    private Device(long ptr) {
        devicePtr = ptr;
    }

    private Device() {
        devicePtr = 0;
    }

    protected void finalize() {
        deInit(devicePtr);
        devicePtr = 0;
    }

    public String getDeviceName() {
        return getDeviceName(devicePtr);
    }

    public Type getType() {
        int type = getType(devicePtr);
        switch(type) {
            case 0: return Type.DEFAULT;
            case 1: return Type.GPU;
            case 2: return Type.FPGA;
            case 4: return Type.CPU;
            case 8: return Type.NOT_CL_CPU;
            case -1:
            default: return Type.INVALID;
        }
    }

    public static Device[] getAllDevices() {
        long[] dds = getAllDevicesNative();
        Device[] devices = new Device[dds.length];
        for (int i = 0; i < dds.length; ++i) {
            devices[i] = new Device(dds[i]);
        }
        return devices;
    }

    public static Device getDefaultDevice() {
        long d = getDefaultDeviceNative();
        return new Device(d);
    }

    public static void setDefaultDevice(Device d) {
        setDefaultDevice(d.devicePtr);
    }

    public String toString() {
        return print(devicePtr);
    }

    private native void deInit(long ptr);

    private native String getDeviceName(long ptr);
    private native int getType(long ptr);

    private static native long[] getAllDevicesNative();
    private static native long getDefaultDeviceNative();
    private static native void setDefaultDevice(long d);

    private native String print(long ptr);
};