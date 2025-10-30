class Solution {
public:
    int lengthOfLongestSubstring(string str) {
        unordered_map<char, int> um;
        int n = str.size();
        int maxlen = 0;

        for (int s = 0, e = 0; s < n && e < n; e++) {
            for (; e < n && um[str[e]] == 0; e++)
                um[str[e]]++;
            um[str[e]]++;
            maxlen = max(maxlen, e - s);

            for (; s < n && um[str[e]] > 1; s++)
                um[str[s]]--;
        }
        return maxlen;
    }
};