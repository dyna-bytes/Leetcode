class Solution {
    /**
    * f(i, m) = max(1 <= x <= 2m){ sum(i ~ i + x) - f(i + x, max(m, x))  }
    */
    int n;
    vector<int> piles;
    vector<vector<int>> dp;
    int f(int i, int m) {
        if (i >= n) return 0;

        int& ret = dp[i][m];
        if (ret != -1) return ret;
        
        int total_suffix = 0;
        for (int j = i; j < n; ++j) total_suffix += piles[j];

        for (int x = 1; x <= min(2*m, n-i); ++x) {
            ret = max(ret, total_suffix - f(i + x, max(m, x)));
        }
        return ret;
    }
public:
    int stoneGameII(vector<int>& piles) {
        this->n = piles.size();
        this->piles = piles;
        dp.assign(n + 1, vector<int>(2 * n, -1));

        return f(0, 1);
    }
};