package com.example;

//import com.clgraph.Data;

public class Main {
    public static void main(String[] args) {
        float tensor[] = { 1.0f, -2.0f, 3.0f, 4.0f };
        long shape[] = { 2, 2 };
        //Data data1 = new Data();//tensor, shape
        System.loadLibrary("OpenCLEvaluationGraphJava");
        System.out.println("ok");

    }
};