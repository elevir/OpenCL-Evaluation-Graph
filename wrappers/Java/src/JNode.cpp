//
// Created by pav on 2019-03-03.
//

#include "com_clgraph_Node.h"

#include "c_cl_graph/ClGraphDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

static_assert(sizeof(jlong) >= sizeof(ClGraphData *), "cannot pass pointer to java with jlong less then size_t");
static_assert(sizeof(jlong) >= sizeof(ClGraphDevice *), "cannot pass pointer to java with jlong less then size_t");
static_assert(sizeof(jlong) >= sizeof(ClGraphNode *), "cannot pass pointer to java with jlong less then size_t");

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_initFromData(JNIEnv *, jobject, jlong data_ptr)
{
    return (jlong)node_data((ClGraphData *)data_ptr);
}

JNIEXPORT void JNICALL Java_com_clgraph_Node_deInit(JNIEnv *, jobject, jlong ptr)
{
    node_destruct((ClGraphNode *)ptr);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_evaluate(JNIEnv *, jclass, jlong ptr)
{
    return (jlong)node_evaluate((ClGraphNode *)ptr);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_addNodeNative(JNIEnv *, jclass, jlong left_ptr, jlong right_ptr, jlong device_ptr)
{
    ClGraphNode * left = (ClGraphNode *)left_ptr;
    ClGraphNode * right = (ClGraphNode *)right_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_add_node(left, right, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_subNodeNative(JNIEnv *, jclass, jlong left_ptr, jlong right_ptr, jlong device_ptr)
{
    ClGraphNode * left = (ClGraphNode *)left_ptr;
    ClGraphNode * right = (ClGraphNode *)right_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_sub_node(left, right, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_unaryMinusNodeNative(JNIEnv *, jclass, jlong op_ptr, jlong device_ptr)
{
    ClGraphNode * op = (ClGraphNode *)op_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_unary_minus_node(op, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_mulNodeNative(JNIEnv *, jclass, jlong left_ptr, jlong right_ptr, jlong device_ptr)
{
    ClGraphNode * left = (ClGraphNode *)left_ptr;
    ClGraphNode * right = (ClGraphNode *)right_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_mul_node(left, right, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_divNodeNative(JNIEnv *, jclass, jlong left_ptr, jlong right_ptr, jlong device_ptr)
{
    ClGraphNode * left = (ClGraphNode *)left_ptr;
    ClGraphNode * right = (ClGraphNode *)right_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_div_node(left, right, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_elemWiseMulNodeNative(JNIEnv *, jclass, jlong left_ptr, jlong right_ptr, jlong device_ptr)
{
    ClGraphNode * left = (ClGraphNode *)left_ptr;
    ClGraphNode * right = (ClGraphNode *)right_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_element_wise_mul_node(left, right, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_elemWiseDivNodeNative(JNIEnv *, jclass, jlong left_ptr, jlong right_ptr, jlong device_ptr)
{
    ClGraphNode * left = (ClGraphNode *)left_ptr;
    ClGraphNode * right = (ClGraphNode *)right_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_element_wise_div_node(left, right, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_absNodeNative(JNIEnv *, jclass, jlong op_ptr, jlong device_ptr)
{
    ClGraphNode * op = (ClGraphNode *)op_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_abs_node(op, device);
}

JNIEXPORT jlong JNICALL Java_com_clgraph_Node_sqrtNodeNative(JNIEnv *, jclass, jlong op_ptr, jlong device_ptr)
{
    ClGraphNode * op = (ClGraphNode *)op_ptr;
    ClGraphDevice * device = (ClGraphDevice *)device_ptr;
    return (jlong)node_abs_node(op, device);
}

#ifdef __cplusplus
}
#endif