class Solution {
public:
    // word2 = word - char
    // len(word2) = word + 1
    int longestStrChain(vector<string>& words) {
        vector<string> sorted_words(words.size());
        for (int i = 0; i < words.size(); i++)
            sorted_words[i] = words[i];

        sort(sorted_words.begin(), sorted_words.end(), [](const string& a, const string& b) {
            if (a.size() == b.size()) return a > b;
            return a.size() > b.size();
        });

        unordered_map<string, int> dp;
        for (auto& word: words) dp[word] = 1;

        int max_len = 1;
        for (string& word: sorted_words) {
            for (int i = 0; i < word.size(); i++) {
                string word2 = word.substr(0, i) + word.substr(i+1);
                if (dp[word2] == 0) continue;

                dp[word2] = max(dp[word2], dp[word] + 1);
                max_len = max(max_len, dp[word2]);
            }
        }
        return max_len;
    }
};