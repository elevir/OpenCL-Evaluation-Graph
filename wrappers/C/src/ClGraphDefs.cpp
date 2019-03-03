//
// Created by pav on 2019-03-02.
//

#include <c_cl_graph/ClGraphDefs.h>

#include "c_cl_graph/ClGraphDefs.h"

#include "cl_graph/Definitions.h"
#include "cl_graph/Data.h"
#include "cl_graph/Device.h"
#include "cl_graph/Node.h"

#include <sstream>

namespace
{
char * print_ss_to_buf(const std::stringstream & ss)
{
    const auto & str = ss.str();
    char * buf = (char *)malloc(sizeof(const char) * str.size() + 1);
    if (!buf) {
        return nullptr;
    }
    for (size_t i = 0; i < str.size(); ++i) {
        buf[i] = str[i];
    }
    buf[str.size()] = 0;
    return buf;
}
}

struct ClGraphData : public cl_graph::Data
{
    ClGraphData() : cl_graph::Data() {};
    ClGraphData(const cl_graph::Data & data) : cl_graph::Data(data) {}
    ClGraphData(ClGraphData &&) = delete;
    ~ClGraphData() override = default;

    ClGraphData & operator=(const ClGraphData &) = delete;
    ClGraphData & operator=(ClGraphData &&) = delete;
};

struct ClGraphDevice : public cl_graph::Device
{
    ClGraphDevice() = delete;
    ClGraphDevice(const cl_graph::Device & device) : cl_graph::Device(device) {}
    ClGraphDevice(ClGraphDevice &&) = delete;
    ~ClGraphDevice() override = default;

    ClGraphDevice & operator=(const ClGraphDevice &) = delete;
    ClGraphDevice & operator=(ClGraphDevice &&) = delete;
};
struct ClGraphNode : public cl_graph::Node
{
    ClGraphNode(const ClGraphData * data) : cl_graph::Node(*data) {}
    ClGraphNode(const cl_graph::Node & node) : cl_graph::Node(node) {}
    ClGraphNode(ClGraphNode &&) = delete;
    ~ClGraphNode() override = default;

    ClGraphNode & operator=(const ClGraphNode &) = delete;
    ClGraphNode & operator=(ClGraphNode &&) = delete;
};

OPENCL_EVAL_C_API ClGraphData * data_empty_create()
{
    return new ClGraphData();
}

ClGraphData * data_create(const float * tensor, size_t size, const size_t * shape, size_t shape_size)
{
    auto data = data_empty_create();
    bool ret = data_upload_data(data, tensor, size, shape, shape_size);
    if (!ret) {
        delete data;
    }
    return data;
}

void data_destruct(ClGraphData * data)
{
    delete data;
}

bool data_upload_data(ClGraphData * data, const float * tensor, size_t size, const size_t * shape, size_t shape_size)
{
    std::vector<float> dt;
    for (size_t i = 0; i < size; ++i) {
        dt.emplace_back(tensor[i]);
    }
    bool ret = data->upload(std::move(dt));
    if (!ret) {
        return false;
    }
    return data_reshape(data, shape, shape_size);
}

bool data_download_data(ClGraphData * data, float ** tensor, size_t * sz, size_t ** shape, size_t * shape_size)
{
    std::vector<float> dt;
    std::vector<size_t> sp;
    if (!data->download(dt, sp)) {
        return false;
    }
    if (*sz < dt.size() || *tensor == nullptr) {
        float * tmp = (float*)realloc(*tensor, sizeof(float) * dt.size());
        if (!tmp) {
            return false;
        }
        (*tensor) = tmp;
    }
    *sz = dt.size();
    memcpy(*tensor, dt.data(), sizeof(float) * dt.size());
    {
        auto tmp_vec = std::move(dt);
    }
    if (*shape_size < sp.size() || *shape == nullptr) {
        size_t * tmp = (size_t*)realloc(*shape, sizeof(size_t) * sp.size());
        if (!tmp) {
            return false;
        }
        (*shape) = tmp;
    }
    *shape_size = sp.size();
    memcpy(*shape, sp.data(), sizeof(size_t) * sp.size());
    return true;
}

bool data_reshape(ClGraphData * data, const size_t * shape, size_t shape_size)
{
    std::vector<size_t> sp;
    for (size_t i = 0; i < shape_size; ++i) {
        sp.emplace_back(shape[i]);
    }
    return data->reshape(std::move(sp));
}

char * data_print(ClGraphData * data)
{
    std::stringstream ss;
    ss << *data;
    return print_ss_to_buf(ss);
}

bool get_all_devices(ClGraphDevice *** devices, size_t * size)
{
    const auto dd = ClGraphDevice::get_all_devices();
    if (dd.size() > *size || *devices == nullptr) {
        ClGraphDevice ** d = (ClGraphDevice**)realloc(devices, sizeof(ClGraphDevice*) * dd.size());
        if (!d) {
            return false;
        }
        (*devices) = d;
    }
    (*size) = dd.size();
    for (size_t i = 0; i < *size; ++i) {
        (*devices)[i] = new ClGraphDevice(dd[i]);
    }
    return true;
}

void devices_destruct(ClGraphDevice ** devices, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        device_destruct(devices[i]);
    }
    free(devices);
}

void device_destruct(ClGraphDevice * device)
{
    delete device;
}

ClGraphDevice * device_get_default()
{
    return new ClGraphDevice(ClGraphDevice::get_default());
}

void set_default(const ClGraphDevice * device)
{
    ClGraphDevice::set_default(*device);
}

const char * get_device_name(ClGraphDevice * device)
{
    return device->get_device_name();
}

int8_t device_get_device_type(ClGraphDevice * device)
{
    return device->get_type();
}

size_t device_get_device_id(ClGraphDevice * device)
{
    return device->get_id();
}

char * device_print(ClGraphDevice * device)
{
    std::stringstream ss;
    ss << (*device);
    return print_ss_to_buf(ss);
}

ClGraphNode * node_add_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::add_node(*left, *right, d));
}

ClGraphNode * node_sub_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::sub_node(*left, *right, d));
}

ClGraphNode * node_unary_minus_node(ClGraphNode * op, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::unary_minus_node(*op, d));
}

ClGraphNode * node_mul_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::mul_node(*left, *right, d));}

ClGraphNode * node_div_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::div_node(*left, *right, d));
}

ClGraphNode * node_element_wise_mul_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::element_wise_mul_node(*left, *right, d));
}

ClGraphNode * node_element_wise_div_node(ClGraphNode * left, ClGraphNode * right, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::element_wise_div_node(*left, *right, d));
}

ClGraphNode * node_abs_node(ClGraphNode * op, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::abs_node(*op, d));
}

ClGraphNode * node_sqrt_node(ClGraphNode * op, const ClGraphDevice * device)
{
    const cl_graph::Device & d = device ? ClGraphDevice::get_default() : *(cl_graph::Device*)device;
    return new ClGraphNode(cl_graph::Node::sqrt_node(*op, d));
}

ClGraphNode * node_data(ClGraphData * data)
{
    return new ClGraphNode(*data);
}

ClGraphData * node_evaluate(ClGraphNode * node)
{
    return new ClGraphData(node->evaluate());
}

void node_destruct(ClGraphNode * node)
{
    delete node;
}

