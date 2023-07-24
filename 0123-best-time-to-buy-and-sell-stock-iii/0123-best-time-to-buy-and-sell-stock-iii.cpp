class Solution {
public:
    int maxProfit(vector<int>& prices) {
        this->n = prices.size();
        this->dp.resize(5, vector<int> (n+1, -1));
        this->prices = prices;
        int ret = money(4, 0);
        return ret;
    }

    
    int money(int transactions, int day) {
        if (day == n) return 0;
        if (transactions == 0) return 0;
        if (dp[transactions][day] != -1) return dp[transactions][day];

        int earned = 0;
        bool buy = (transactions % 2 == 0);
        if (buy)
            earned = money(transactions - 1, day + 1) - prices[day];
        else // sell
            earned = money(transactions - 1, day + 1) + prices[day];

        return dp[transactions][day] = max(money(transactions, day + 1), earned);
    }
private:
    int n;
    vector<vector<int>> dp;
    vector<int> prices;
};