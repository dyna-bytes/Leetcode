class Solution {
    vector<vector<int>> dp;
    int lcs(int a, int b, string& str1, string& str2) {
        if (a == str1.size() || b == str2.size()) return 0;
        
        int& ret = dp[a][b];
        if (ret != -1) return ret;

        ret = lcs(a + 1, b, str1, str2);
        ret = max(ret, lcs(a, b + 1, str1, str2));
        if (str1[a] == str2[b])
            ret = max(ret, 1 + lcs(a + 1, b + 1, str1, str2));

        return ret;
    }
    void trackback(int a, int b, string& str1, string& str2, string& ret) {
        if (a == str1.size() && b == str2.size()) return;
        else if (a == str1.size()) {
            ret = str2.substr(b);
            return;
        }
        else if (b == str2.size()) {
            ret = str1.substr(a);
            return;
        }
        
        if (lcs(a, b, str1, str2) == lcs(a + 1, b, str1, str2)){
            trackback(a + 1, b, str1, str2, ret);
            ret = str1[a] + ret;
        }
        else if (lcs(a, b, str1, str2) == lcs(a, b + 1, str1, str2)){
            trackback(a, b + 1, str1, str2, ret);
            ret = str2[b] + ret;
        }
        else if (lcs(a, b, str1, str2) == 1 + lcs(a + 1, b + 1, str1, str2)) {
            trackback(a + 1, b + 1, str1, str2, ret);
            ret = str1[a] + ret;
        }
    }
public:
    string shortestCommonSupersequence(string str1, string str2) {
        dp.resize(str1.size(), vector<int>(str2.size(), -1));
        
        int common = lcs(0, 0, str1, str2);

        string str = "";
        trackback(0, 0, str1, str2, str);

        return str;
    }
};