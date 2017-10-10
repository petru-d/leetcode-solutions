#include <string>
#include <vector>
#include <iostream>

std::string digit_to_letters[10] = { "", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

void print_vect_str(const std::vector<std::string>& vs)
{
    std::cout << "[";

    auto it = vs.begin();
    std::cout << *it;
    for (++it; it != vs.end(); ++it)
    {
        std::cout <<  ", " << *it;
    }

    std::cout << "]" << std::endl;
}

std::vector<std::string> letterCombinations(std::string digits)
{
    if (0 == digits.length()) return {};
    if (1 == digits.length())
    {
        std::vector<std::string> result(digit_to_letters[digits[0] - '0'].length());
        int i = 0;
        for (auto l : digit_to_letters[digits[0] - '0'])
        {
            result[i++] = std::string(1, l);
        }
        return result;
    }

    auto lessDigits = letterCombinations(digits.substr(0, digits.size() - 1));
    auto oneDigit = letterCombinations(digits.substr(digits.size() - 1));

    std::vector<std::string> combo;

    for (auto& ld : lessDigits)
        for (const auto& od : oneDigit)
        {
            combo.push_back(ld + od);
        }

    return combo;
}

int main()
{
    print_vect_str(letterCombinations("27"));
    return 0;
}

