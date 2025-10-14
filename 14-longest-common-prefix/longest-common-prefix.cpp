class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix;
        for (int i = 0; i < strs[0].size(); i++) {
            char ch = strs[0][i];

            for (string& str: strs) {
                if (str.size() <= i) return prefix;
                if (str[i] != ch) return prefix;
            }
            prefix += ch;
        }
        return prefix;
    }
};