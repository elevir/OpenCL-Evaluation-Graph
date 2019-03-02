#pragma once

#include "Data.h"

#include <jni.h>

class JData :
    public cl_graph::Data
{
    JData(JNIEnv * jni_env, jobject jobject, jboolean derived);

private:
    jobject jObject;
    JNIEnv * env;
    jmethodID jTest;
};