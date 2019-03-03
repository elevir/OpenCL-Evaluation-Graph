package com.clgraph;

public class Node {

    long nodePtr;

    static {
        System.loadLibrary("OpenCLEvaluationGraphJava");
    }

    private Node(long ptr) {
        nodePtr = ptr;
    }

    public Node() {
        nodePtr = 0;
    }

    public Node(Data data) {
        nodePtr = initFromData(data.dataPtr);
    }

    public Data evaluate() {
        return new Data(evaluate(nodePtr));
    }

    public static Node addNode(Node left, Node right, Device device) {
        return new Node(addNodeNative(left.nodePtr, right.nodePtr, device.devicePtr));
    }
    public static Node subNode(Node left, Node right, Device device) {
        return new Node(subNodeNative(left.nodePtr, right.nodePtr, device.devicePtr));
    }
    public static Node unaryMinusNode(Node op, Device device) {
        return new Node(unaryMinusNodeNative(op.nodePtr, device.devicePtr));
    }
    public static Node mulNode(Node left, Node right, Device device) {
        return new Node(mulNodeNative(left.nodePtr, right.nodePtr, device.devicePtr));
    }
    public static Node divNode(Node left, Node right, Device device) {
        return new Node(divNodeNative(left.nodePtr, right.nodePtr, device.devicePtr));
    }
    public static Node elemWiseMulNode(Node left, Node right, Device device) {
        return new Node(elemWiseMulNodeNative(left.nodePtr, right.nodePtr, device.devicePtr));
    }
    public static Node elemWiseDivNode(Node left, Node right, Device device) {
        return new Node(elemWiseDivNodeNative(left.nodePtr, right.nodePtr, device.devicePtr));
    }
    public static Node absNode(Node op, Device device) {
        return new Node(absNodeNative(op.nodePtr, device.devicePtr));
    }
    public static Node sqrtNode(Node op, Device device) {
        return new Node(sqrtNodeNative(op.nodePtr, device.devicePtr));
    }

    protected void finalize() {
        deInit(nodePtr);
        nodePtr = 0;
    }

    private native long initFromData(long dataPtr);
    private native void deInit(long ptr);

    private static native long evaluate(long nodePtr);

    private static native long addNodeNative(long left, long right, long device);
    private static native long subNodeNative(long left, long right, long device);
    private static native long unaryMinusNodeNative(long op, long device);
    private static native long mulNodeNative(long left, long right, long device);
    private static native long divNodeNative(long left, long right, long device);
    private static native long elemWiseMulNodeNative(long left, long right, long device);
    private static native long elemWiseDivNodeNative(long left, long right, long device);
    private static native long absNodeNative(long op, long device);
    private static native long sqrtNodeNative(long op, long device);
};