class Solution {
    typedef pair<int, int> pii;
    vector<pii> sets;
    vector<vector<vector<int>>> dp;
    int f(int curr, int m, int n) {
        if (curr == sets.size()) return 0;

        int& ret = dp[curr][m][n];
        if (ret != -1) return ret;

        auto [zero, one] = sets[curr];
        if (zero <= m && one <= n) {
            ret = max(ret, 1 + f(curr + 1, m - zero, n - one));
        }
        ret = max(ret, f(curr + 1, m, n));
        return ret;
    }
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        dp.resize(strs.size() + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        for (string& str: strs) {
            int ones = 0, zeros = 0;
            for (char ch: str)
                if (ch == '0') zeros++;
                else ones++;

            sets.push_back({zeros, ones});
        }

        return f(0, m, n);
    }
};