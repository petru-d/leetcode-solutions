#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace Solution
{
    enum class PatternType
    {
        Letter,
        Dot,
        LetterStar,
        DotStar
    };

    struct PatternToken
    {
        PatternType Type;

        // Not relevant for dot pattern.
        char Letter;
    };

    // No checks.
    PatternToken GetPatternToken(const string& p, int start_index)
    {
        if ('.' == p[start_index])
        {
            if (p.size() - 1 == start_index || p[1 + start_index] != '*') return { PatternType::Dot, '_' };
            return { PatternType::DotStar, '_' };
        }

        if (p.size() - 1 == start_index || p[1 + start_index] != '*') return { PatternType::Letter, p[start_index] };

        return { PatternType::LetterStar, p[start_index] };
    }

    bool isMatch_naive(string s, int index_s, string p, int index_p)
    {
        int S = int(s.size());
        int P = int(p.size());

        // If the input is done.
        if (S == index_s)
        {
            // If the pattern is also done - match.
            if (P == index_p) return true;

            //We also allow star patterns here.
            auto token = GetPatternToken(p, index_p);
            if (token.Type == PatternType::Dot || token.Type == PatternType::Letter) return false;

            return isMatch_naive(s, index_s, p, 2 + index_p);
        }

        // the input is not done (see above), but the pattern is done - no match.
        if (P == index_p) return false;

        auto token = GetPatternToken(p, index_p);

        if (PatternType::Letter == token.Type)
        {
            // letter must match
            return s[index_s] == token.Letter ? isMatch_naive(s, 1 + index_s, p, 1 + index_p) : false;
        }

        if (PatternType::Dot == token.Type)
        {
            return isMatch_naive(s, 1 + index_s, p, 1 + index_p);
        }

        // greedy first match
        if (PatternType::LetterStar == token.Type)
        {
            auto pos_non_letter = int(s.find_first_not_of(token.Letter, index_s));
            if (string::npos == pos_non_letter)
                pos_non_letter = S;

            for (int i = pos_non_letter; i >= index_s; --i)
            {
                if (isMatch_naive(s, i, p, 2 + index_p)) return true;
            }

            return false;
        }

        // greedy first match
        if (PatternType::DotStar == token.Type)
        {
            for (int i = S; i >= index_s; --i)
            {
                if (isMatch_naive(s, i, p, 2 + index_p)) return true;
            }

            return false;
        }

        // Should not get here.
        return false;
    }

    //dissapointing naive solution :(
    bool isMatch_naive(const string& s, const string& p)
    {
        return isMatch_naive(s, 0, p, 0);
    }

    // Dynamic Programming solution (from leetcode)
    bool isMatch_dp(const string& s, const string& p) 
    {
        /**
        * f[i][j]: if s[0..i-1] matches p[0..j-1]
        * if p[j - 1] != '*'
        *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
        * if p[j - 1] == '*', denote p[j - 2] with x
        *      f[i][j] is true iff any of the following is true
        *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
        *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
        * '.' matches any single character
        */
        int m = int(s.size()), n = int(p.size());
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

        f[0][0] = true;
        for (int j = 1; j <= n; j++)
            f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j - 1] != '*')
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
                else
                    // p[0] cannot be '*' so no need to check "j > 1" here
                    f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

        return f[m][n];
    }

    bool isMatch(string s, string p)
    {
        return isMatch_dp(s, p);
    }
}

int main()
{
    cout << Solution::isMatch("aa", "a") << "\n";
    cout << Solution::isMatch("aa", "aa") << "\n";
    cout << Solution::isMatch("aaa", "aa") << "\n";
    cout << Solution::isMatch("aa", "a*") << "\n";
    cout << Solution::isMatch("aa", ".*") << "\n";
    cout << Solution::isMatch("ab", ".*") << "\n";
    cout << Solution::isMatch("aab", "c*a*b") << "\n";
    cout << Solution::isMatch("a", "ab*") << "\n";
    cout << Solution::isMatch("acaabbaccbbacaabbbb", "a*.*b*.*a*aa*a*") << "\n";
    return 0;
}

