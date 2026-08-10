class Solution {
    vector<int> dp;
    int f(int n) {
        if (n == 0) return false;

        int& ret = dp[n];
        if (ret != -1) return ret;

        ret = false;
        for (int x = 1; x * x <= n; x++) {
            ret = max(ret, (int)!f(n - x * x));
        }
        return ret;
    }
public:
    bool winnerSquareGame(int n) {
        dp.assign(n + 1, -1);
        return f(n);
    }
};