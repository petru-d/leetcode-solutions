#include <string>
#include <iostream>

using namespace std;

int myCtoi(char c)
{
	return c - '0';
}

bool myIsWhite(char c)
{
	return ' ' == c || '\t' == c || '\r' == c || '\n' == c;
}

int myIsSign(char c)
{
	if ('-' == c) return -1;
	if ('+' == c) return 1;
	return 0;
}

int myAtoi(string str)
{
	constexpr int ErrorCode = 0;
	//[ \t]*[-+]?[0-9]*[ \t]**

	//Error code and result at the same time? :D
	if (str.empty()) return ErrorCode;

	//Deal with whitespace padding.
	string::size_type posNonWhite{ 0 };
	while (myIsWhite(str[posNonWhite])) ++posNonWhite;
	str = str.substr(posNonWhite);
	if (str.empty()) return ErrorCode;
	posNonWhite = str.length() - 1;
	while (myIsWhite(str[posNonWhite])) --posNonWhite;
	str = str.substr(0, posNonWhite + 1);
	if (str.empty()) return ErrorCode;

	//Deal with the initial sign.
	bool negative = (-1 == myIsSign(str[0]));
	if (0 != myIsSign(str[0]))
	{
		str = str.substr(1);
	}
	if (str.empty()) return ErrorCode;

	auto make_return = [negative](int64_t rawResult)
	{
		rawResult = negative ? -rawResult : rawResult;

		if (rawResult < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
		if (rawResult > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();

		return int(rawResult);
	};

	int digitsCounter = 0;
	int64_t result = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		// Stop at the first non-accepted character and return what we have.
		if ('0' > str[i] || '9' < str[i]) return make_return(result);

		result = result * 10 + myCtoi(str[i]);
		++digitsCounter;

		if (11 == digitsCounter) return make_return(result);
	}

	return make_return(result);
}

int main()
{
	cout << myAtoi("20") << endl;
	cout << myAtoi("-20") << endl;
	cout << myAtoi("+") << endl;
	cout << myAtoi("+1") << endl;
	cout << myAtoi("    010") << endl;
	cout << myAtoi("  -0012a42") << endl;
	cout << myAtoi("2147483648") << endl;
	cout << myAtoi("9223372036854775809") << endl;
    return 0;
}

