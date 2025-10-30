class Solution {
public:
    int lengthOfLongestSubstring(string str) {
        unordered_map<char, int> um;
        int n = str.size();
        int maxlen = 0;

        for (int s = 0, e; s < n; s++) {
            um.clear();
            for (e = s; e < n; e++) {
                if (um[str[e]]) break;
                um[str[e]] = true;
            }
            maxlen = max(maxlen, e - s);
        }
        return maxlen;
    }
};