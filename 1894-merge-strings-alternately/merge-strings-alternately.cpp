class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string ret;
        for (int a = 0, b = 0; a < word1.size() || b < word2.size(); ) {
            if (a < word1.size())
                ret.push_back(word1[a++]);
            if (b < word2.size())
                ret.push_back(word2[b++]);
        }
        return ret;
    }
};