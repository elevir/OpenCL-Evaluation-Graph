#include <limits.h>
#include <cl_graph/Device.h>
#include <cl_graph/Data.h>
#include <cl_graph/Node.h>
#include "gtest/gtest.h"
namespace {

using namespace cl_graph;

struct NodeMulTest
	: public ::testing::Test
{
	NodeMulTest()
	{
		m_device = find_device();
	}

	Device find_device()
	{
		const auto & devices = Device::get_all_devices();
		auto it = std::find_if(devices.begin(), devices.end(), [] (const Device & d) { return d.get_type() == Device::GPU; });
		if (it != devices.end()) {
			return *it;
		}
		return Device::get_default();
	}

	Device m_device;
};

TEST_F(NodeMulTest, TensorXScalarTest)
{
	float cnst = 7;
	float data1[5][2][3] = {{{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}},
							{{7.0f, 8.0f, 9.0f}, {10.0f, 11.0f, 12.0f}},
							{{13.0f, 14.0f, 15.0f}, {16.0f, 17.0f, 18.0f}},
							{{19.0f, 20.0f, 21.0f}, {22.0f, 23.0f, 24.0f}},
							{{25.0f, 26.0f, 27.0f}, {28.0f, 29.0f, 30.0f}}};
	Data a = data1;
	Data b = cnst;
	auto node1 = Node::mul_node(a, b, m_device);
	auto node2 = Node::mul_node(b, a, m_device);
	auto res1 = node1.evaluate();
	auto res2 = node2.evaluate();
	float out1[5][2][3];
	float out2[5][2][3];
	ASSERT_TRUE(res1.get_shaped_data(out1)) << "could not extract shaped data: " << res1;
	ASSERT_TRUE(res2.get_shaped_data(out2)) << "could not extract shaped data: " << res2;
	for (size_t i = 0; i < std::size(data1); ++i) {
		for (size_t j = 0; j < std::size(data1[i]); ++j) {
			for (size_t k = 0; k < std::size(data1[i][j]); ++k) {
				EXPECT_EQ(data1[i][j][k] * cnst, out1[i][j][k]) << "incorrect constant multiplication";
				EXPECT_EQ(data1[i][j][k] * cnst, out2[i][j][k]) << "incorrect constant multiplication";
			}
		}
	}
}

TEST_F(NodeMulTest, TensorXTensorFail)
{
    float data1[5][2][3] = {{{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}},
                            {{7.0f, 8.0f, 9.0f}, {10.0f, 11.0f, 12.0f}},
                            {{13.0f, 14.0f, 15.0f}, {16.0f, 17.0f, 18.0f}},
                            {{19.0f, 20.0f, 21.0f}, {22.0f, 23.0f, 24.0f}},
                            {{25.0f, 26.0f, 27.0f}, {28.0f, 29.0f, 30.0f}}};
    Data a = data1;
    Data b = data1;

    auto node1 = Node::mul_node(a, b, m_device);
    auto res1 = node1.evaluate();
    ASSERT_TRUE(res1.empty()) << "data is not empty: " << res1;
}

TEST_F(NodeMulTest, MatrixXMatrix)
{
    float data1[5][3] = {{ 1,  2,  3},
                         { 7,  8,  9},
                         {13, 14, 15},
                         {19, 20, 21},
                         {25, 26, 27}};

	float data2[3][4] = {{1.5f,  2.5f,  3.5f,  1.0f},
						 {7.5f,  8.5f,  9.5f,  10.5f},
						 {13.5f, 14.5f, 15.5f, 10.5f}};
    Data a = data1;
    Data b = data2;

    auto node1 = Node::mul_node(a, b, m_device);
    auto res = node1.evaluate();
	float expected_res[5][4] = {{57,  63,  69,  53.5},
								{192, 216, 240, 185.5},
								{327, 369, 411, 317.5},
								{462, 522, 582, 449.5},
								{597, 675, 753, 581.5}};
	float out[5][4];
	ASSERT_TRUE(res.get_shaped_data(out)) << "cannot extract data from res: " << res;
    for (size_t i = 0; i < std::size(out); ++i) {
    	for (size_t j = 0; j < std::size(out[i]); ++j) {
    		EXPECT_EQ(out[i][j], expected_res[i][j]) << "result is not as expected at pos [" << i << "][" << j << "]";
    	}
    }
}

TEST_F(NodeMulTest, MatrixXVector)
{
	float data1[5][3] = {{ 1,  2,  3},
						 { 7,  8,  9},
						 {13, 14, 15},
						 {19, 20, 21},
						 {25, 26, 27}};
	float vector[3] = { 1, 2, 3 };
	Data a = data1;
	Data vec = vector;

	auto node1 = Node::mul_node(a, vec, m_device);
	auto node2 = Node::mul_node(vec, a, m_device);
	auto res1 = node1.evaluate();
	auto res2 = node2.evaluate();
	ASSERT_TRUE(res2.empty()) << "unexpected result is not empty for product of incompatible dims, res: " << res2;
	float expected_res[5] = { 14, 50, 86, 122, 158 };
	float out[5];
	ASSERT_TRUE(res1.get_shaped_data(out)) << "cannot extract data from res: " << res1;
	for (size_t i = 0; i < std::size(out); ++i) {
		EXPECT_EQ(out[i], expected_res[i]) << "result is not as expected at pos [" << i << "]";
	}
}

TEST_F(NodeMulTest, VectorXMatrix)
{
	float data1[5][3] = {{ 1,  2,  3},
						 { 7,  8,  9},
						 {13, 14, 15},
						 {19, 20, 21},
						 {25, 26, 27}};
	float vector[5] = { 1, 2, 3, 4, 5 };
	Data a = data1;
	Data vec = vector;

	auto node1 = Node::mul_node(a, vec, m_device);
	auto node2 = Node::mul_node(vec, a, m_device);
	auto res1 = node1.evaluate();
	auto res2 = node2.evaluate();
	ASSERT_TRUE(res1.empty()) << "unexpected result is not empty for product of incompatible dims, res: " << res1;
	float expected_res[3] = { 255, 270, 285 };
	float out[3];
	ASSERT_TRUE(res2.get_shaped_data(out)) << "cannot extract data from res: " << res1;
	for (size_t i = 0; i < std::size(out); ++i) {
		EXPECT_EQ(out[i], expected_res[i]) << "result is not as expected at pos [" << i << "]";
	}
}

} // namespace