#include "ManagedData.h"
#include <algorithm>

using namespace CLGraph;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

Data::Data()
{
	m_data = new NativeData();
}

Data::!Data()
{
	delete m_data;
}

Data::Data(float scalar)
{
	m_data = new NativeData(scalar);
}

Data::Data(array<float>^ container, array<SIZE_T>^ shape)
{
	std::vector<float> umContainer;
	InteropUtilities::CopyManagedArrayToVector(container, umContainer);
	std::vector<size_t> umShape(shape->Length);
	InteropUtilities::CopyManagedArrayToVector(shape, umShape);
	m_data = new NativeData(umContainer, umShape);
}

Data::Data(NativeData* nativeData)
{
	m_data = nativeData;
}

Data::operator Data^(array<float>^ data)
{
	Data^ result = gcnew Data();
	result->SetShapedData(data);
	return result;
}

Data::operator Data^(array<double>^ data)
{
	Data^ result = gcnew Data();
	result->SetShapedData(data);
	return result;
}

NativeData *Data::GetNativeData()
{
	return m_data;
}

bool CLGraph::Data::Download(array<float>^ data, array<SIZE_T>^ shape)
{
	std::vector<float> umData(data->Length);
	std::vector<size_t> umShape(shape->Length);
	InteropUtilities::CopyManagedArrayToVector(data, umData);
	InteropUtilities::CopyManagedArrayToVector(shape, umShape);
	return m_data->download(umData, umShape);
}

bool CLGraph::Data::Upload(array<float>^ data, array<SIZE_T>^ shape)
{
	std::vector<float> umData(data->Length);
	std::vector<size_t> umShape(shape->Length);
	InteropUtilities::CopyManagedArrayToVector(data, umData);
	InteropUtilities::CopyManagedArrayToVector(shape, umShape);
	return m_data->upload(umData, umShape);
}

bool CLGraph::Data::Empty()
{
	return m_data->empty();
}

bool CLGraph::Data::GetShapedData(array<float>^% shapedData)
{
	std::vector<float> umShapedData;
	bool result = m_data->get_shaped_data(umShapedData);
	if (result)
		InteropUtilities::CopyVectorToManagedArray(umShapedData, shapedData);
	return result;
}

bool CLGraph::Data::SetShapedData(array<float>^ shapedData)
{
	std::vector<float> umShapedData(shapedData->Length);
	InteropUtilities::CopyManagedArrayToVector(shapedData, umShapedData);
	return m_data->set_shaped_data(umShapedData);
}

bool CLGraph::Data::GetShapedData(array<double>^% shapedData)
{
	throw gcnew System::NotImplementedException();
	/*std::vector<double> umShapedData;
	bool result = m_data->get_shaped_data(umShapedData);
	if (result)
		InteropUtilities::CopyVectorToManagedArray(umShapedData, shapedData);
	return result;*/
}

bool CLGraph::Data::SetShapedData(array<double>^ shapedData)
{
	throw gcnew System::NotImplementedException();
	/*std::vector<double> umShapedData(shapedData->Length);
	InteropUtilities::CopyManagedArrayToVector(shapedData, umShapedData);
	return m_data->set_shaped_data(umShapedData);*/
}