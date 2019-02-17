#include <limits.h>
#include <Data.h>
#include <Node.h>
#include "gtest/gtest.h"
namespace {

// Data tests.

// Data constructor/destructor tests.
TEST(DataTest, ConstructorDestructorTest) {
	{
		cl_graph::Data data1;
		EXPECT_TRUE("Empty cl_graph::Data object created successfully");

		std::vector<float> vector{ 1.0f, 2.0f, 3.0f };
		std::vector<size_t> shapeVector{ 3 };
		cl_graph::Data data2(vector, shapeVector);
		EXPECT_NO_FATAL_FAILURE();
		// Data object created successfully from a std::vector<float>.

		cl_graph::Data data3(data2);
		EXPECT_NO_FATAL_FAILURE();
		// Data object created successfully from another Data object.

		cl_graph::Data data4(std::move(data3));
		EXPECT_NO_FATAL_FAILURE();
		// Data object created successfully from another Data object using std::move semantics.
	}
	EXPECT_NO_FATAL_FAILURE();
	// All cl_graph::Data objects were destructed successfully.
}

// Data upload/download tests.
TEST(DataTest, UploadDownloadTest) {
	std::vector<float> vector{ 1.0f, 2.0f, 3.0f };
	std::vector<size_t> shapeVector{ 3 };
	cl_graph::Data data;
	data.upload(vector, shapeVector);
	std::vector<float> checkVector;
	std::vector<size_t> checkShapeVector;
	data.download(checkVector, checkShapeVector);
	EXPECT_EQ(checkVector[0], vector[0]);
	EXPECT_EQ(checkVector[1], vector[1]);
	EXPECT_EQ(checkVector[2], vector[2]);
	EXPECT_EQ(checkShapeVector[0], shapeVector[0]);
	// 1d-vector data uploaded and downloaded from and to Data object.

	std::vector<float> vector2d{ 11.0f, 22.0f, 33.0f, 44.0f, 55.0f, 66.0f, 77.0f, 88.0f, 99.0f };
	std::vector<size_t> shapeVector2d{ 3, 3 };
	cl_graph::Data data2d;
	data2d.upload(vector2d, shapeVector2d);
	std::vector<float> checkVector2d;
	std::vector<size_t> checkShapeVector2d;
	data2d.download(checkVector2d, checkShapeVector2d);
	for (int i = 0; i < 9; ++i)
	{
		EXPECT_EQ(checkVector2d[i], vector2d[i]);
	}
	EXPECT_EQ(checkShapeVector2d[0], shapeVector2d[0]);
	EXPECT_EQ(checkShapeVector2d[1], shapeVector2d[1]);
	// 2d-vector data uploaded and downloaded from and to Data object.
}

} // namespace