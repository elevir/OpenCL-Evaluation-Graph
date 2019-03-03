#include "Data.h"
#include "Node.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <stddef.h>
#include <vector>

int main()
{
    auto devices = cl_graph::Device::get_all_devices();
    for (const auto & dev : devices) {
        std::cout << dev << std::endl;
    }
    // construct graph
    std::array<std::array<float, 2>, 2> matrix1 = {
        std::array<float, 2> {1.0f, -2.0f},
        {3.0f, 4.0f}
    };
    cl_graph::Data data1 = matrix1;

    cl_graph::Data data2 = {{5.0f, 6.0f}, {-7.0f, 8.0f}};
    cl_graph::Data scalar = 9;

    auto add_node = cl_graph::Node::add_node(data1, data2);
    auto add_scalar = add_node + scalar;
    // get result
    auto add_result = add_scalar.evaluate();

    // output result
    std::cout << "A:\n" << data1 << '\n';
    std::cout << "+\n";
    std::cout << "B:\n" << data2 << '\n';
    std::cout << "+\n";
    std::cout << "C:\n" << scalar << '\n';
    std::cout << "=\n";
    std::cout << add_result << "\n\n";

    auto sub_node = cl_graph::Node::sub_node(data1, data2);
    auto sub_result = sub_node.evaluate();

    // output result
    std::cout << "A:\n" << data1 << '\n';
    std::cout << "-\n";
    std::cout << "B:\n" << data2 << '\n';
    std::cout << "=\n";
    std::cout << sub_result << "\n\n";


    auto elem_wise_mul = cl_graph::Node::element_wise_mul_node(data1, data2);
    auto elem_wise_scalar = cl_graph::Node::element_wise_mul_node(elem_wise_mul, scalar);

    auto elem_wise_result = elem_wise_mul.evaluate();

    // output result
    std::cout << "A:\n" << data1 << '\n';
    std::cout << ".*\n";
    std::cout << "B:\n" << data2 << '\n';
    std::cout << ".*\n";
    std::cout << "C:\n" << scalar << '\n';
    std::cout << "=\n";
    std::cout << elem_wise_result << "\n\n";

    auto elem_wise_div = cl_graph::Node::element_wise_div_node(data1, data2);
    auto elem_wise_scalar_div = cl_graph::Node::element_wise_div_node(elem_wise_div, scalar);

    auto elem_wise_div_result = elem_wise_div.evaluate();
    auto elem_wise_div_scalar_result = elem_wise_scalar_div.evaluate();

    // output result
    std::cout << "A:\n" << data1 << '\n';
    std::cout << "./\n";
    std::cout << "B:\n" << data2 << '\n';
    std::cout << "=\n";
    std::cout << "C:\n" << elem_wise_div_result << "\n";
    std::cout << "./\n";
    std::cout << scalar << '\n';
    std::cout << "C':\n" << elem_wise_div_scalar_result << "\n\n";

    auto abs_data1 = cl_graph::Node::abs_node(data1);
    auto abs_data2 = cl_graph::Node::abs_node(data2);

    auto abs_data1_result = abs_data1.evaluate();
    auto abs_data2_result = abs_data2.evaluate();

    std::cout << "abs(A):\n" << abs_data1_result << '\n';
    std::cout << "abs(B):\n" << abs_data2_result << '\n';

    auto sqrt_data1 = cl_graph::Node::sqrt_node(data1);
    auto sqrt_data2 = cl_graph::Node::sqrt_node(data2);

    auto sqrt_data1_result = sqrt_data1.evaluate();
    auto sqrt_data2_result = sqrt_data2.evaluate();

    std::cout << "sqrt(A):\n" << sqrt_data1_result << '\n';
    std::cout << "sqrt(B):\n" << sqrt_data2_result << '\n';
}