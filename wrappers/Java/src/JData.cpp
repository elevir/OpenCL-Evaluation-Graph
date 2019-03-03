#include "com_clgraph_Data.h"

#include "ClGraphDefs.h"

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_clgraph_Data_init(JNIEnv *, jobject)
{
    assert(sizeof(jlong) >= sizeof(size_t) && "cannot pass pointer to java with jlong less then size_t");
    return (jlong)data_empty_create();
}

JNIEXPORT jboolean JNICALL Java_com_clgraph_Data_upload (JNIEnv * env, jobject, jlong ptr, jfloatArray tensor, jlongArray shape)
{
    auto sz = env->GetArrayLength(tensor);
    auto shape_sz = env->GetArrayLength(shape);
    auto dt = env->GetFloatArrayElements(tensor, nullptr);
    auto sh = env->GetLongArrayElements(shape, nullptr);
    std::vector<size_t> shape_sz_t;
    for (size_t i = 0; i < shape_sz; ++i) {
        shape_sz_t.emplace_back(sh[i]);
    }
    ClGraphData * data = (ClGraphData *)ptr;
    bool ret = data_upload_data(data, dt, sz, shape_sz_t.data(), shape_sz);
    env->ReleaseFloatArrayElements(tensor, dt, 0);
    env->ReleaseLongArrayElements(shape, sh, 0);
    return ret;
}

JNIEXPORT jfloatArray JNICALL Java_com_clgraph_Data_getData(JNIEnv * env, jobject, jlong ptr)
{
    float * tensor = nullptr;
    size_t sz = 0;
    size_t * shape = nullptr;
    size_t shape_sz = 0;
    ClGraphData * data = (ClGraphData *)ptr;
    auto ret = data_download_data(data, &tensor, &sz, &shape, &shape_sz);
    if (!ret) {
        return nullptr;
    }
    free(shape);
    auto arr = env->NewFloatArray(sz);
    if (!arr) {
        return nullptr;
    }
    auto elems = env->GetFloatArrayElements(arr, nullptr);
    for (size_t i = 0; i < sz; ++i) {
        elems[i] = tensor[i];
    }
    free(tensor);
    env->ReleaseFloatArrayElements(arr, elems, 0);
    return arr;
}

JNIEXPORT jlongArray JNICALL Java_com_clgraph_Data_getShape(JNIEnv * env, jobject, jlong ptr)
{
    float * tensor = nullptr;
    size_t sz = 0;
    size_t * shape = nullptr;
    size_t shape_sz = 0;
    ClGraphData * data = (ClGraphData *)ptr;
    auto ret = data_download_data(data, &tensor, &sz, &shape, &shape_sz);
    if (!ret) {
        return nullptr;
    }
    free(tensor);
    auto arr = env->NewLongArray(shape_sz);
    if (!arr) {
        return nullptr;
    }
    auto elems = env->GetLongArrayElements(arr, nullptr);
    for (size_t i = 0; i < shape_sz; ++i) {
        elems[i] = shape[i];
    }
    free(shape);
    env->ReleaseLongArrayElements(arr, elems, 0);
    return arr;
}

JNIEXPORT jstring JNICALL Java_com_clgraph_Data_print(JNIEnv * env, jobject, jlong ptr)
{
    ClGraphData * data = (ClGraphData *)ptr;
    char * buf = data_print(data);
    auto str = env->NewStringUTF(buf);
    free(buf);
    return str;
}

#ifdef __cplusplus
}
#endif