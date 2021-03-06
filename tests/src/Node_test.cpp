#include <limits.h>
#include <cl_graph/Device.h>
#include <cl_graph/Data.h>
#include <cl_graph/Node.h>
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
	cl_graph::Data data1(vector1);
	cl_graph::Data data2(vector2);
	cl_graph::Node dataNode1(data1);
	cl_graph::Node dataNode2(data2);
	cl_graph::Node additionNode = cl_graph::Node::add_node(dataNode1, dataNode2);
	cl_graph::Data resultData = additionNode.evaluate();
	std::vector<float> result;
	std::vector<size_t> resultShape;
	resultData.download(result, resultShape);
  ASSERT_FALSE(resultShape.empty());
	EXPECT_EQ(vector1.size(), resultShape[0]);
	for (int i = 0; i < 3; ++i) EXPECT_EQ(result[i], vector1[i] + vector2[i]);
	// 1d Node addition evaluation.
}

} // namespace