#include <vector>
#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Solution
{
	int make_hash(const vector<string>& words)
	{
		return std::accumulate(words.begin(), words.end(), 0, [](int i, const string& word)
		{
			return i + std::accumulate(word.begin(), word.end(), 0, [](int i, char c) {return i + int(c); });
		});
	}

	bool test_index(const string& s, int index, const vector<string>& words)
	{
		vector<string> s_words(words.size());

		auto one_word_size = words[0].length();
		for (size_t i = 0; i < words.size(); ++i)
		{
			s_words[i] = s.substr(index + i * one_word_size, one_word_size);
		}

		sort(s_words.begin(), s_words.end());

		return words == s_words;
	}

	vector<int> findSubstring(string s, vector<string>& words)
	{
		// Test if at all possible.
		auto all_words_size = words.size() * words[0].length();
		if (s.size() < all_words_size) return{};

		// Prepare the words.
		sort(words.begin(), words.end());
		auto words_hash = make_hash(words);

		vector<int> result;

		// Hash and test the first window.
		auto current_hash = make_hash({ s.substr(0, all_words_size) });
		if (words_hash == current_hash && test_index(s, 0, words)) result.push_back(0);

		// Rehash and test subsequent windows.
		for (int i = 1; i <= int(s.length()) - all_words_size; ++i)
		{
			current_hash = current_hash - s[i - 1] + s[i + all_words_size - 1];

			if (words_hash == current_hash && test_index(s, i, words)) result.push_back(i);
		}

		return result;
	}
}

int main()
{
	vector<string> words = { "foo", "bar" };
	auto sol = Solution::findSubstring("barfoothefoobarman", words);
	for (const auto& s : sol)
	{
		cout << s << endl;
	}

	return 0;
}