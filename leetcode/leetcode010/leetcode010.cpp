#include <string>
#include <iostream>

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
    bool isMatch_naive(string s, string p)
    {
        return isMatch_naive(s, 0, p, 0);
    }

    bool isMatch(string s, string p)
    {
        
    }
}

int main()
{
    cout << Solution::isMatch_naive("aa", "a") << "\n";
    cout << Solution::isMatch_naive("aa", "aa") << "\n";
    cout << Solution::isMatch_naive("aaa", "aa") << "\n";
    cout << Solution::isMatch_naive("aa", "a*") << "\n";
    cout << Solution::isMatch_naive("aa", ".*") << "\n";
    cout << Solution::isMatch_naive("ab", ".*") << "\n";
    cout << Solution::isMatch_naive("aab", "c*a*b") << "\n";
    cout << Solution::isMatch_naive("a", "ab*") << "\n";
    cout << Solution::isMatch_naive("acaabbaccbbacaabbbb", "a*.*b*.*a*aa*a*") << "\n";
    return 0;
}

