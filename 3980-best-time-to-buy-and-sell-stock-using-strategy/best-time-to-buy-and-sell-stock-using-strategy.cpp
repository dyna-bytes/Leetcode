#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)

class Solution {
    typedef long long ll;
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int N = prices.size();
        ll profit = 0;
        for (int i = 0; i < N; i++) {
            profit += ((ll)prices[i] * strategy[i]);
        }

        vector<ll> hold_diff(N, 0), sell_diff(N, 0);
        for (int i = 0; i < N; i++) {
            hold_diff[i] = (ll)prices[i] * (0 - strategy[i]);
            sell_diff[i] = (ll)prices[i] * (1 - strategy[i]);
        }
        
        vector<ll> psum_hold_diff(N + 1, 0), psum_sell_diff(N + 1, 0); // prefix sum [s, e)
        for (int i = 0; i < N; i++) {
            psum_hold_diff[i + 1] = psum_hold_diff[i] + hold_diff[i];
            psum_sell_diff[i + 1] = psum_sell_diff[i] + sell_diff[i];
        }

        ll max_profit = profit;
        for (int i = 0; i < N - k + 1; i++) {
            ll diff = (psum_hold_diff[i + k/2] - psum_hold_diff[i]);
            diff += (psum_sell_diff[i + k] - psum_sell_diff[i + k/2]);
            max_profit = max(max_profit, profit + diff);
        }

        return max_profit;
    }
};