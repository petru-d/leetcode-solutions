#include <vector>
#include <iostream>
#include "../utils/printing.h"

using namespace std;

namespace Solution
{
	void rotate_4(int& a, int& b, int& c, int& d)
	{
		auto aux{ d };
		d = c;
		c = b;
		b = a;
		a = aux;
	}

	void rotate(vector<vector<int>>& matrix) 
	{
		auto n{ matrix.size() };
		auto n2{ n / 2 };

		// Rotate the 4 quarters.
		for (auto i = 0; i < n2; ++i)
			for (auto j = 0; j < n2; ++j)
				rotate_4(matrix[i][j], matrix[j][n - i - 1], matrix[n - i - 1][n - j - 1], matrix[n - j - 1][i]);

		// For odd numbers, rotate the middle 4 axes.
		if (1 == n % 2)
		{
			for (auto i = 0; i < n2; ++i)
				rotate_4(matrix[i][n2], matrix[n2][n - i - 1], matrix[n - i - 1][n2], matrix[n2][i]);
		}
	}
}

int main()
{
	vector<vector<int>> matrix = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, { 13, 14, 15, 16 } };
	Solution::rotate(matrix);
	print_vector_vector(cout, matrix); cout << endl;

	matrix = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9} };
	Solution::rotate(matrix);

	print_vector_vector(cout, matrix); cout << endl;

    return 0;
}

