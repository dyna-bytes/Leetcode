class Solution {
    int n;
    vector<int> prices;
    vector<vector<vector<int>>> dp;
    const int IMP = -1e9;
    int f(int curr, int k, int buys) {
        if (curr == n) return 0;

        // int ret = IMP;
        int& ret = dp[curr][k][buys];
        if (ret != IMP) return ret;

        if (k > 0 && buys == 0)
            ret = max(ret, -prices[curr] + f(curr + 1, k - 1, buys + 1));
        if (buys > 0)
            ret = max(ret, prices[curr] + f(curr + 1, k, buys - 1));
        
        ret = max(ret, f(curr + 1, k, buys));
        return ret;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        this->n = prices.size();
        this->prices = prices;
        dp.resize(n+1, vector<vector<int>>(k+1, vector<int>(k+1, IMP)));
        return f(0, k, 0);
    }
};