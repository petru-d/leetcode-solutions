// leetcode50.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

double myPow(double x, int n)
{
	// -2147483648 will overflow when negated. Simplest solution is to increase the amount of bits used :D
	int64_t nn(n);
	bool negative = false;
	if (n < 0)
	{
		negative = true;
		nn = -nn;
	}

	double result = 1;
	while (0 != nn)
	{
		if (nn & 1) result *= x;
		x *= x;
		nn >>= 1;
	}

	return negative ? 1 / result : result;
}

int main()
{
	std::cout << myPow(3, 2) << "\n";

	std::cout << myPow(1, -2147483647 - 1) << "\n";

	
	std::cout << myPow(3, 3) << "\n";
	std::cout << myPow(3, 4) << "\n";
	
	return 0;
}

