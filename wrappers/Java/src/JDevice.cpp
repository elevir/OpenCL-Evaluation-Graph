//
// Created by pav on 2019-03-03.
//

#include "com_clgraph_Device.h"

#include "c_cl_graph/ClGraphDefs.h"

#include <cstdlib>

#ifdef __cplusplus
extern "C" {
#endif

static_assert(sizeof(jlong) >= sizeof(ClGraphDevice *), "cannot pass pointer to java with jlong less then size_t");

JNIEXPORT void JNICALL Java_com_clgraph_Device_deInit(JNIEnv *, jobject, jlong ptr)
{
    ClGraphDevice * device = (ClGraphDevice *)ptr;
    device_destruct(device);
}

JNIEXPORT jstring JNICALL Java_com_clgraph_Device_getDeviceName(JNIEnv * env, jobject, jlong ptr)
{
    ClGraphDevice * device = (ClGraphDevice *)ptr;
    const char * buf = get_device_name(device);
    auto str = env->NewStringUTF(buf);
    return str;
}

JNIEXPORT jint JNICALL Java_com_clgraph_Device_getType(JNIEnv *, jobject, jlong ptr)
{
    ClGraphDevice * device = (ClGraphDevice *)ptr;
    if (device) {
        return device_get_device_type(device);
    }
    return -1;
}

JNIEXPORT jlongArray JNICALL Java_com_clgraph_Device_getAllDevicesNative(JNIEnv * env, jclass)
{
    ClGraphDevice ** devices = nullptr;
    size_t sz = 0;
    if (!get_all_devices(&devices, &sz)) {
        sz = 0;
    }
    auto arr = env->NewLongArray(sz);
    auto elems = env->GetLongArrayElements(arr, nullptr);
    for (size_t i = 0; i < sz; ++i) {
        elems[i] = (jlong)devices[i];
    }
    env->ReleaseLongArrayElements(arr, elems, 0);
    devices_destruct(devices, sz);
    return arr;
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Device_getDefaultDeviceNative(JNIEnv *, jclass)
{
    return (jlong)device_get_default();
}

JNIEXPORT void JNICALL Java_com_clgraph_Device_setDefaultDevice(JNIEnv *, jclass, jlong ptr)
{
    if (ptr) {
        set_default((ClGraphDevice *) ptr);
    }
}

JNIEXPORT jstring JNICALL Java_com_clgraph_Device_print(JNIEnv * env, jobject, jlong ptr)
{
    ClGraphDevice * device = (ClGraphDevice *)ptr;
    char * buf = device_print(device);
    auto str = env->NewStringUTF(buf);
    free(buf);
    return str;
}

#ifdef __cplusplus
}
#endif