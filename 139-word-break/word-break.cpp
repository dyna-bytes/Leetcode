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
        dp.resize(s.size() + 1, -1);
        return wrdBrk(s, wordDict);
    }
};