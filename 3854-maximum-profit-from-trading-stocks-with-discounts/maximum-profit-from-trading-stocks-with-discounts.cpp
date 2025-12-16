class Solution {
    int n;
    int budget;
    vector<vector<int>> childs;
    vector<int> present;
    vector<int> future;
    vector<vector<vector<int>>> dp; // dp[cost][bought]

    // return dp_ret[cost] = profit
    vector<int> dfs(int curr, int parent_bought) {
        vector<int>& ret = dp[curr][parent_bought];
        if (ret != vector<int>(budget + 1, -1e9)) return ret;

        int price = present[curr - 1];
        if (parent_bought) price /= 2;
        int profit = future[curr - 1] - price;

        vector<int> dp_skip(budget + 1, -1e9);
        dp_skip[0] = 0;
        for (int child: childs[curr]) {
            dp_skip = merge(dp_skip, dfs(child, false));
        }

        vector<int> dp_buy(budget + 1, -1e9);
        if (price <= budget) {
            dp_buy[price] = profit;
            for (int child: childs[curr]) {
                dp_buy = merge(dp_buy, dfs(child, true));
            }
        }

        for (int i = 0; i <= budget; i++)
            ret[i] = max(dp_skip[i], dp_buy[i]);
        return ret;
    }

    vector<int> merge(const vector<int>& dp_acc, const vector<int>& dp_new) {
        vector<int> dp_ret(budget + 1, -1e9);

        for (int cost_acc = 0; cost_acc <= budget; cost_acc++) {
            if (dp_acc[cost_acc] == -1e9) continue;
            for (int cost_new = 0; cost_new + cost_acc <= budget; cost_new++) {
                if (dp_new[cost_new] == -1e9) continue;
                dp_ret[cost_acc + cost_new] = max(
                    dp_ret[cost_acc + cost_new],
                    dp_acc[cost_acc] + dp_new[cost_new]
                );
            }
        }
        return dp_ret;
    }
    
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        this->n = n;
        this->budget = budget;
        this->present = present;
        this->future = future;

        dp.resize(n + 1, vector<vector<int>>(2, vector<int>(budget + 1, -1e9)));

        childs.resize(n+1);
        for (auto& hier: hierarchy) {
            int u = hier[0], v = hier[1];
            childs[u].push_back(v);
        }

        vector<int> ret = dfs(1, false);
        return *max_element(ret.begin(), ret.end());
    }
};