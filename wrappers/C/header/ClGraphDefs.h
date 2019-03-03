//
// Created by pav on 2019-03-02.
//

#pragma once

#ifndef OPENCL_EVAL_C_API
#  ifdef WIN32
#    ifdef OpenCLGraphCExport
#      define OPENCL_EVAL_C_API __declspec(dllexport)
#    else
#      define OPENCL_EVAL_C_API __declspec(dllimport)
#    endif
#  else
#    define OPENCL_EVAL_C_API
#  endif // WIN32
#endif // !OPENCL_EVAL_C_API

#include <cstddef>
#include <cstdint>

extern "C" {

struct OPENCL_EVAL_C_API ClGraphData;
struct OPENCL_EVAL_C_API ClGraphDevice;
struct OPENCL_EVAL_C_API ClGraphNode;

// ClGraphData
OPENCL_EVAL_C_API ClGraphData * data_create(const float * tensor, size_t size, const size_t * shape, size_t shape_size);
OPENCL_EVAL_C_API void data_destruct(ClGraphData * data);
OPENCL_EVAL_C_API bool data_upload_data(ClGraphData * data, const float * tensor, size_t size, const size_t * shape, size_t shape_size);
OPENCL_EVAL_C_API bool data_download_data(ClGraphData * data, float ** tensor, size_t * size, size_t ** shape, size_t * shape_size);
OPENCL_EVAL_C_API bool data_reshape(ClGraphData * data, const size_t * shape, size_t shape_size);
OPENCL_EVAL_C_API char * data_print(ClGraphData * data);

// ClGraphDevice
OPENCL_EVAL_C_API bool get_all_devices(ClGraphDevice *** devices, size_t * size);
OPENCL_EVAL_C_API void devices_destruct(ClGraphDevice ** devices, size_t size);
OPENCL_EVAL_C_API ClGraphDevice * device_get_default();
OPENCL_EVAL_C_API void set_default(const ClGraphDevice * device);

OPENCL_EVAL_C_API const char * get_device_name(ClGraphDevice * device);
OPENCL_EVAL_C_API int8_t get_device_type(ClGraphDevice * device);
OPENCL_EVAL_C_API size_t get_device_id(ClGraphDevice * device);
OPENCL_EVAL_C_API char * device_print(ClGraphDevice * device);

// Nodes
OPENCL_EVAL_C_API ClGraphNode * node_data(ClGraphData * data);
OPENCL_EVAL_C_API ClGraphNode * node_add_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_sub_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_unary_minus_node(ClGraphNode * op, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_mul_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_div_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_element_wise_mul_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_element_wise_div_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_abs_node(ClGraphNode * op, const ClGraphDevice * device);
OPENCL_EVAL_C_API ClGraphNode * node_sqrt_node(ClGraphNode * op, const ClGraphDevice * device);
OPENCL_EVAL_C_API void node_destruct(ClGraphNode * node);

}