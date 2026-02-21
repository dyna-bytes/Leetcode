class Solution {
    vector<int> dp;
    bool is_prime(int n) {
        int& ret = dp[n];
        if (ret != -1) return ret;

        if (n < 2) return ret = false;
        if (n == 2 || n == 3) return ret = true;
        if (n % 2 == 0) return ret = false;

        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return ret = false;
        }
        return ret = true;
    }
public:
    int countPrimeSetBits(int left, int right) {
        dp.resize(1e6 + 1, -1);

        int ret = 0;
        for (int i = left; i <= right; ++i) {
            int cnt = __builtin_popcount(i);
            if (is_prime(cnt)) ret++;
        }
        return ret;
    }
};