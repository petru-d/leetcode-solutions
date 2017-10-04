#include <vector>
#include <unordered_map>
#include <iostream>
#include "../utils/printing.h"

using namespace std;

namespace Solution
{
	vector<int> twoSum(vector<int>& nums, int target)
	{
		unordered_map<int, int> complements_to_indices;

		for (auto i = 0; i < nums.size(); ++i)
		{
			auto pos = complements_to_indices.find(target - nums[i]);
			if (pos != complements_to_indices.end())
			{
				return { i, pos->second };
			}
			complements_to_indices.insert({ nums[i], i });
		}

		return { -1, -1 };
	}
}

int main()
{
	vector<int> v;

	v = { 2, 7, 11, 15 };
	print_vector(cout, Solution::twoSum(v, 9));

	v = { 3, 2, 4 };
	print_vector(cout, Solution::twoSum(v, 6));

	return 0;
}

