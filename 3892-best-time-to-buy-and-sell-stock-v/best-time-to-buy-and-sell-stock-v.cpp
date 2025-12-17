class Solution {
    typedef long long ll;
    #define IDLE 0
    #define LONG 1
    #define SHORT 2
    int n;
    vector<int> prices;
    vector<vector<vector<ll>>> dp;

    // i번째 날까지 k 번의 transaction이 완료되고 state 상태임.
    ll dfs(int i, int k, int state) {
        if (i == n) return (state == IDLE) ? 0 : -1e9;
        if (k == 0) return 0;

        ll& ret = dp[i][k][state];
        if (ret != -1) return ret;

        if (state == IDLE) {
            ret = max({
                dfs(i + 1, k, IDLE),
                -prices[i] + dfs(i + 1, k, LONG),
                prices[i] + dfs(i + 1, k, SHORT)
            });
        } else if (state == LONG) {
            ret = max({
                dfs(i + 1, k, LONG),
                prices[i] + dfs(i + 1, k - 1, IDLE)
            });
        } else if (state == SHORT) {
            ret = max({
                dfs(i + 1, k, SHORT),
                -prices[i] + dfs(i + 1, k - 1, IDLE),
            });
        }

        return ret;
    }
public:
    long long maximumProfit(vector<int>& prices, int k) {
        n = prices.size();
        this->prices = prices;
        dp.resize(n + 1, vector<vector<ll>>(k + 1, vector<ll>(3, -1)));

        return dfs(0, k, IDLE);
    }
};