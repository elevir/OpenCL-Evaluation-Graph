#include <limits.h>
#include <Device.h>
#include <Data.h>
#include <Node.h>
#include "gtest/gtest.h"
namespace {

// Node tests.

// Node constructor/destructor tests.
TEST(NodeTest, ConstructorDestructorTest) {
	{
		cl_graph::Data data1;
		cl_graph::Data data2;
		cl_graph::Node dataNode1(data1);
		cl_graph::Node dataNode2(data2);
		cl_graph::Node additionNode = cl_graph::Node::add_node(dataNode1, dataNode2);
	}
	EXPECT_NO_FATAL_FAILURE();
	// All Node objects were destructed successfully.
}

TEST(NodeAddTest, EvaluationTest) {
	std::vector<float> vector1{ 1.0f, 2.0f, 3.0f };
	std::vector<float> vector2{ 1.0f, 2.0f, 3.0f };
	std::vector<size_t> shapeVector{ 3 };
	cl_graph::Data data1(vector1, shapeVector);
	cl_graph::Data data2(vector2, shapeVector);
	cl_graph::Node dataNode1(data1);
	cl_graph::Node dataNode2(data2);
	cl_graph::Node additionNode = cl_graph::Node::add_node(dataNode1, dataNode2);
	cl_graph::Data resultData = additionNode.evaluate();
	std::vector<float> result;
	std::vector<size_t> resultShape;
	resultData.download(result, resultShape);
	EXPECT_EQ(shapeVector[0], resultShape[0]);
	for (int i = 0; i < 3; ++i) EXPECT_EQ(result[i], vector1[i] + vector2[i]);
	// 1d Node addition evaluation.
}

} // namespace