#include "Node.h"

#include <algorithm>
#include <iostream>
#include <stddef.h>
#include <vector>

int main() {

    auto devices = cl_graph::Device::get_all_devices();
    const auto it = std::find_if(devices.begin(), devices.end(),
                                 [](const auto & d) { return d.get_type() == cl_graph::Device::CPU; });
    if (it == devices.end()) {
        std::cerr << "No needed device" << std::endl;
        return -1;
    }
    auto device = *it;
    // construct graph
    cl_graph::Data data1 = cl_graph::Data({1.0f, -2.0f, 3.0f, 4.0f}, {2, 2});
    cl_graph::Data data2 = cl_graph::Data({5.0f, 6.0f, -7.0f, 8.0f}, {2, 2});
    cl_graph::Data scalar = cl_graph::Data(9.0);

    auto add_node = cl_graph::Node::add_node(data1, data2, device);
    auto add_scalar = cl_graph::Node::add_node(add_node, scalar, device);
    // get result
    auto add_result = add_scalar.evaluate();

    // output result
    std::cout << "A matrix:\n" << data1 << '\n';
    std::cout << "+\n";
    std::cout << "B matrix:\n" << data2 << '\n';
    std::cout << "=\n";
    std::cout << "C matrix:\n" << add_result << "\n\n";

    auto elem_wise_mul = cl_graph::Node::element_wise_mul_node(data1, data2, device);
    auto elem_wise_scalar = cl_graph::Node::element_wise_mul_node(elem_wise_mul, scalar, device);

    auto elem_wise_result = elem_wise_scalar.evaluate();

    // output result
    std::cout << "A matrix:\n" << data1 << '\n';
    std::cout << ".*\n";
    std::cout << "B matrix:\n" << data2 << '\n';
    std::cout << "=\n";
    std::cout << "C matrix:\n" << elem_wise_result << "\n\n";

    auto abs_data1 = cl_graph::Node::abs_node(data1, device);
    auto abs_data2 = cl_graph::Node::abs_node(data2, device);

    auto abs_data1_result = abs_data1.evaluate();
    auto abs_data2_result = abs_data2.evaluate();

    std::cout << "abs(A) matrix:\n" << abs_data1_result << '\n';
    std::cout << "abs(B) matrix:\n" << abs_data2_result << '\n';

    auto sqrt_data1 = cl_graph::Node::sqrt_node(data1, device);
    auto sqrt_data2 = cl_graph::Node::sqrt_node(data2, device);

    auto sqrt_data1_result = sqrt_data1.evaluate();
    auto sqrt_data2_result = sqrt_data2.evaluate();

    std::cout << "sqrt(A) matrix:\n" << sqrt_data1_result << '\n';
    std::cout << "sqrt(B) matrix:\n" << sqrt_data2_result << '\n';
}