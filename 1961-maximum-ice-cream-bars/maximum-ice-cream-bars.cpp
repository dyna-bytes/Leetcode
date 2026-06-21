class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
    #define maxn (int)(1e5 + 5)
    int count[maxn];
public:
    int maxIceCream(vector<int>& costs, int coins) {
        memset(count, 0, sizeof(count));

        int max_cost = 0;
        for (int cost: costs) {
            count[cost]++;
            max_cost = max(max_cost, cost);
        }
        
        int ret = 0;
        for (int cost = 1; cost <= max_cost; ++cost) {
            if (count[cost] == 0) continue;
            if (coins <= 0) break;
            while (count[cost] && coins >= cost) {
                coins -= cost;
                count[cost]--;
                ret++;
            }
        }
        return ret;
    }
};