#include <string>
#include <iostream>

/*
0   8
1  79
2 6
35
4
*/

/*
a  g  m                 0  6         
b fh ln                 1 57
ce ik o                 24 8
d  j  p                 3  9
*/

/*
a e i m                 0 4 8
bdfhjln                 13579
c g k o                 2 6
*/

std::string convert(std::string s, int numRows)
{
    if (0 >= numRows) return "";
    if (1 == numRows) return s;

    std::string result(s);

    int k = 0;
    auto l = int(s.length());
    for (int r = 0; r < numRows; ++r)
    {
        int i = r;
        int firstDiff = 2 * (numRows - 1 - r);
        int secondDiff = 2 * r;

        bool useFirstDiff = r < numRows - 1; //start with the second diff (will be non zero) in case of the last row

        bool swapDiffs = (0 != r && numRows - 1 != r); //alternate between diffs for internal rows only

        while (i < l)
        {
            result[k] = s[i];
            i += useFirstDiff ? firstDiff : secondDiff;
            if (swapDiffs) useFirstDiff = !useFirstDiff;
            ++k;
        }
    }

    return result;
}

int main()
{
    std::cout << convert("0123456789", 3) << std::endl;
    std::cout << convert("0123456789", 4) << std::endl;
    std::cout << convert("PAYPALISHIRING", 3) << std::endl;
    return 0;
}

