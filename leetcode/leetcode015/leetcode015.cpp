#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_map>

#include "../utils/printing.h"

using namespace std;

namespace Solution
{
	vector<vector<int>> threeSum1(vector<int>& nums)
	{
		auto comp = [](const vector<int>& v1, const vector<int>& v2)
		{
			auto iv1 = v1.begin();
			auto iv2 = v2.begin();

			while (v1.end() != iv1 && v2.end() != iv2)
			{
				if (*iv1 != *iv2) return *iv1 < *iv2;
				++iv1; ++iv2;
			}
			if (iv1 == v1.end() && iv2 != v2.end()) return true;
			return false;
		};
		auto solution = set<vector<int>, decltype(comp)>(comp);

		sort(nums.begin(), nums.end());

		auto nums_c = nums.size();

		unordered_map<int, set<int>> opposites;
		for (auto n = 0; n < nums_c; ++n)
		{
			auto oppos = opposites.find(nums[n]);
			if (oppos == opposites.end()) opposites.insert({ nums[n], {n} });
			else oppos->second.insert(n);
		}

		for (auto i = 0; i < nums_c; ++i)
		{
			if (0 != i && nums[i] == nums[i - 1]) continue;
			for (auto j = i + 1; j < nums_c; ++j)
			{
				if (nums[i] + nums[j] > -nums[0]) break;
				if (i + 1 != j && nums[j] == nums[j - 1]) continue;
				auto oppos(opposites.find(-nums[i] - nums[j]));
				if (oppos != opposites.end() && oppos->second.end() != find_if(oppos->second.begin(), oppos->second.end(), [i, j](int k) {
					return i != k && j != k; 
				}))
				{
					vector<int> s = { nums[i] , nums[j], -nums[i] - nums[j] };
					sort(s.begin(), s.end());
					solution.insert(s);
				}
			}
		}

		vector<vector<int>> result;
		for (const auto& s : solution)
		{
			result.emplace_back(s);
		}
		return result;
	}

	int binary_search(const vector<int>& nums, int start, int end, int target)
	{
		if (start + 1 >= end) return target == nums[start] ? start : -1;

		int pivot_index = (start + end) / 2;
		int pivot = nums[pivot_index];

		if (target == pivot) return pivot_index;

		if (target < pivot) return binary_search(nums, start, pivot_index, target);

		return binary_search(nums, pivot_index, end, target);
	}

	vector<vector<int>> threeSum2(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());

		auto nums_c = nums.size();

		vector<vector<int>> result;

		for (auto i = 0; i < nums_c; ++i)
		{
			if (0 != i && nums[i] == nums[i - 1]) continue;
			for (auto j = i + 1; j < nums_c - 1; ++j)
			{
				if (nums[i] + nums[j] > -nums[0]) break;
				if (i + 1 != j && nums[j] == nums[j - 1]) continue;

				auto k = binary_search(nums, (int)j + 1, int(nums.size()), -nums[i] - nums[j]);
				if (-1 == k) continue;

				result.push_back({ nums[i], nums[j], nums[k] });
			}
		}
		
		return result;
	}

	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> result;

		sort(nums.begin(), nums.end());

		auto nums_c = nums.size();
		for (auto i = 0; i < nums_c; ++i)
		{
			auto target = -nums[i];

			auto front = i + 1;
			auto back = nums_c - 1;

			// Approach front and back. On each iteration we take only one step, which guarantees that at some point we'll end up with either front or back on the foot of the outermost solution.
			// After that, only the other pointer will advance until we end up with both legs on the outermost solution.
			while (front < back)
			{
				auto partial_sum = nums[front] + nums[back];

				if (partial_sum < target)
				{
					++front;
				}
				else if (partial_sum > target)
				{
					--back;
				}
				else
				{
					std::vector<int> triplet{ nums[i], nums[front], nums[back] };

					// Eliminate duplicates. Both loops execute at least once.
					// A new solution must have both legs different than the current one and they both have to be inside the legs of the current.
					while (front < back && nums[front] == triplet[1]) ++front;
					while (front < back && nums[back] == triplet[2]) --back;

					result.emplace_back(triplet);
				}
			}

			// Skip duplicates of the first number.
			while (i + 1 < nums_c && nums[i + 1] == nums[i]) ++i;
		}

		return result;
	}
}

int main()
{
	vector<int> v;

	v = { -6, 1, 2, 4, 5 };
	print_vector_vector(cout, Solution::threeSum(v));
	cout << endl;

	v = { 0, 0};
	print_vector_vector(cout, Solution::threeSum(v));
	cout << endl;

	v = { 0, 0, 0};
	print_vector_vector(cout, Solution::threeSum(v));
	cout << endl;

	v = { -4, -1, -1, 0, 1, 2};
	print_vector_vector(cout, Solution::threeSum(v));
	cout << endl;

	return 0;
}

/*

a1 <= ... <= ai <= ... aj <= ... <= an

ai + aj = t;

ak + al < t -> ++k
ak + al > t -> --l

- each step where the sum is not "t", either one of the steps closes to the correct leg



- 6 1 2 4 5

*/