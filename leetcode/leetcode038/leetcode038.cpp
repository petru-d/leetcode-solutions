#include <string>
#include <vector>
#include <iostream>

std::string getNextSay(std::string say)
{
    auto say_length(say.length());
    std::string::size_type currentPos{ 0 };

    std::vector<std::pair<char, char>> nextSay;
    while (say_length > currentPos)
    {
        auto oldCurrentPos{ currentPos };
        auto currentChar{ say[currentPos]};
        while (say[currentPos] == currentChar)
        {
            ++currentPos;
            if (currentPos == say_length) break;
        }
        nextSay.emplace_back(char((currentPos - oldCurrentPos) + '0'), currentChar);
    }

    std::string nextSayStr(2 * nextSay.size(), 'x');
    int i = 0;
    for (const auto& s : nextSay)
    {
        nextSayStr[i++] = s.first;
        nextSayStr[i++] = s.second;
    }

    return nextSayStr;
}

std::string countAndSay(int n)
{
    if (1 == n) return "1";

    return getNextSay(countAndSay(n - 1));
}


int main()
{
    for (int i = 1; i < 20; ++i)
    {
        std::cout << countAndSay(i) << std::endl;
    }

    return 0;
}

