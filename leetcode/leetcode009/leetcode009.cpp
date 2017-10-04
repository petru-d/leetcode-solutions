// leetcode9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <iostream>

int digits_no(int x)
{
	if (0 == x) return 1;

	int result = 0;
	while (0 != x)
	{
		x = x / 10;
		++result;
	}

	return result;
}

bool isPalindrome(int x)
{
	if (0 > x) return false;
	if (x < 10) return true;

	auto last_digit = std::div(x, 10).rem;
	if (0 == last_digit) return false;

	auto digits_no_x = digits_no(x);
	auto one_followed_by_zeros = int(pow(10, digits_no_x - 1));
	auto first_digit = std::div(x, one_followed_by_zeros).quot;

	if (last_digit != first_digit) return false;

	int next_check = (x - first_digit * one_followed_by_zeros - last_digit) / 10;

	if (0 == next_check) return true;

	auto diff_digits_no = digits_no_x - digits_no(next_check);
	
	auto trailing = std::div(next_check, int(pow(10, diff_digits_no - 2)));

	if (0 != trailing.rem) return false;

	return isPalindrome(trailing.quot);
}

bool isPalindrome2(int x)
{
	if (0 > x) return false;
	if (0 == x) return true;
	if (x % 10 == 0) return false;

	int reversed = 0;
	while (x > reversed)
	{
		auto div10 = std::div(x, 10);

		reversed = 10 * reversed + div10.rem;

		x = div10.quot;
	}

	return (x == reversed) || (x == reversed / 10);
}

int main()
{
	std::cout << (!isPalindrome2(10) ? "10 OK" : "10 KO") << std::endl;
	std::cout << (isPalindrome2(11) ? "11 OK" : "11 KO") << std::endl;

	std::cout << (isPalindrome2(1000110001) ? "1000110001 OK" : "1000110001 KO") << std::endl;

	std::cout << (isPalindrome2(121) ? "121 OK" : "121 KO") << std::endl;
	std::cout << (!isPalindrome2(1000021) ? "1000021 OK" : "1000021 KO") << std::endl;
	
	

    return 0;
}

