class Solution {
    int n;
    vector<int> nums;
    const int INF = 1e9;
    vector<vector<int>> dp;
    int f(int i, int mod) {
        if (i == n) {
            if (mod == 0) return 0;
            return -INF;
        }

        int& ret = dp[i][mod];
        if (ret != -1) return ret;
        ret = f(i+1, mod);
        ret = max(ret, nums[i] + f(i+1, (mod + nums[i]) % 3));
        return ret;
    }
public:
    int maxSumDivThree(vector<int>& nums) {
        n = nums.size();
        this->nums = nums;
        dp.resize(n+1, vector<int>(3, -1));

        return f(0, 0);
    }
};

/*
 * dp[pos][mod] : maximum possible sum from pos where the current sum modulo 3 is mod.
 * dp[pos][mod] = max(dp[pos+1][mod], 
 *                  nums[i] + dp[pos+1][(mod + nums[i]) % 3])
 * dp[n][0] = 0
 * dp[n][1] = -INF
 * dp[n][2] = -INF
*/