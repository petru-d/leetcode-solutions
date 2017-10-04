#pragma once
#include <vector>
#include <algorithm>
template<typename T, typename V>
T* linked_list_from_vector(const std::vector<V>& data)
{
	T* result = nullptr;

	std::for_each(data.rbegin(), data.rend(), [&result](V v) {auto newResult = new T(v);  newResult->next = result; result = newResult; });

	return result;
}