class Solution {
    vector<int> dp;
    bool isMatch(string& s, string& word) {
        if (s.size() < word.size()) return false;
        return s.substr(0, word.size()) == word;
    }
public:
    bool wrdBrk(string& s, vector<string>& wordDict) {
        int& ret = dp[s.size()];
        if (s.size() == 0) return ret = true;
        if (ret != -1) return ret;

        ret = false;
        for (string& word: wordDict) {
            if (isMatch(s, word)) {
                string substr = s.substr(word.size());
                ret |= wrdBrk(substr, wordDict);
            }
        }
        return ret;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        int N = s.size();
        dp.resize(N + 1, 0);

        for (int i = 0; i < N; i++) {
            string curr_s = s.substr(i);

            for (string& word: wordDict) {
                if (isMatch(curr_s, word)) {
                    if (i == 0) dp[i] = true;
                    if (dp[i] == true) dp[i + word.size()] = true;
                }
            }
        }
        return dp[N];
    }
};