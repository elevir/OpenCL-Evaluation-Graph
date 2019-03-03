package com.example;

import com.clgraph.Data;
import com.clgraph.Device;
import com.clgraph.Node;

public class Main {
    public static void main(String[] args) {
        Device device = Device.getDefaultDevice();
        System.out.println(device);
        float[] tensor1 = { 1.0f, -2.0f, 3.0f, 4.0f };
        long[] shape1 = { 2, 2 };
        Data data1 = new Data(tensor1, shape1);
        float[] tensor2 = { 5.0f, 6.0f, -7.0f, 8.0f, };
        long[] shape2 = { 2, 2 };
        Data data2 = new Data(tensor2, shape2);
        Data scalar = new Data(9.0f);
        System.out.println(data1);
        System.out.println(data2);
        System.out.println(scalar);
        Node addNode = Node.addNode(new Node(data1), new Node(data2), device);
        Node addScalar = Node.addNode(addNode, new Node(scalar), device);

        Data res = addScalar.evaluate();
        System.out.println(data1);
        System.out.println("+");
        System.out.println(data2);
        System.out.println("+");
        System.out.println(scalar);
        System.out.println("=");
        System.out.println(res);
        System.out.println();
    }
};