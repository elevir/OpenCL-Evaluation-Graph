#pragma once
#include <vector>

#ifdef _WIN64
#define SIZE_T System::UInt64
#else
#define SIZE_T System::UInt32
#endif // _WIN64

namespace InteropUtilities
{
	template<class T>
	void CopyManagedArrayToVector(array<T>^ managedArray, std::vector<T>& vector)
	{
		vector.resize(managedArray->Length);
		pin_ptr<T> containerPtr = &managedArray[0];
		std::memcpy(vector.data(), containerPtr, vector.size() * sizeof(T));
	}

	template<class T>
	void CopyVectorToManagedArray(const std::vector<T>& vector, array<T>^% managedArray)
	{
		managedArray = gcnew array<T>(vector.size());
		pin_ptr<T> p = &managedArray[0];
		std::memcpy(p, vector.data(), managedArray->Length * sizeof(T));
	}
}

