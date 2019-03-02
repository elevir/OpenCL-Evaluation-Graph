#pragma once
#include <Data.h>
#include "Utilities.hpp"

namespace CLGraph {

	typedef cl_graph::Data NativeData;

    public ref class Data sealed
    {
	public:
		!Data();
		Data();
		Data(float scalar);
		Data(array<float>^ container, array<SIZE_T>^ shape);

		bool Download(array<float>^ data, array<SIZE_T>^ shape);
		bool Upload(array<float>^ data, array<SIZE_T>^ shape);
		bool Empty();
		bool GetShapedData(array<float>^% shapedData);
		bool GetShapedData(array<double>^% shapedData);
		bool SetShapedData(array<float>^ shapedData);
		bool SetShapedData(array<double>^ shapedData);
		virtual System::String^ ToString() override;


		static operator Data^(array<float>^ data);
		static operator Data^(array<double>^ data);

	internal:
		Data(NativeData* nativeData);
		NativeData* GetNativeData();
		
	private:
		NativeData* m_data;
	};

}