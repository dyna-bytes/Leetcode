class Solution {
    bool isMatch(string& s, string& word) {
        if (s.size() < word.size()) return false;
        return s.substr(0, word.size()) == word;
    }
    void wrdBrk(string& s, vector<string>& wordDict, string& chosen, vector<string>& ret) {
        if (s.size() == 0) {
            ret.push_back(chosen);
            return;
        }

        bool isChosenNull = (chosen.size() == 0);

        for (string& word: wordDict) {
            if (isMatch(s, word)) {
                string substr = s.substr(word.size());
                if (isChosenNull)
                    chosen = word;
                else
                    chosen = chosen + " " + word;
                wrdBrk(substr, wordDict, chosen, ret);
                if (isChosenNull)
                    chosen = "";
                else
                    chosen = chosen.substr(0, chosen.size() - word.size() - 1);
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> ret;
        string chosen;
        wrdBrk(s, wordDict, chosen, ret);
        return ret;
    }
};