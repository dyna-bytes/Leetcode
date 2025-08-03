class Solution {
    vector<vector<int>> dp;
    int func(int a, int b, string& text1, string& text2) {
        if (a == text1.size() || b == text2.size()) return 0;

        int& ret = dp[a][b];
        if (ret != -1) return ret;
        
        ret = func(a + 1, b, text1, text2);
        ret = max(ret, func(a, b + 1, text1, text2));

        if (text1[a] == text2[b])
            ret = max(ret, 1 + func(a + 1, b + 1, text1, text2));
        return ret;
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        dp.resize(text1.size(), vector<int>(text2.size(), -1));
        return func(0, 0, text1, text2);
    }
};