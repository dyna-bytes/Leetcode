class Solution {
    typedef long long ll;
    const ll mod = 1e9 + 7;
    vector<ll> dp;
    
    ll pow_mod(ll base, ll exp) {
        ll result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }

    ll fact(int n) {
        if (n == 0) return 1;
        if (n == 1) return 1;
        ll& ret = dp[n];
        if (ret != -1) return ret;
        return ret = n * fact(n - 1) % mod;
    }
    
    ll combi2(int n) {
        if (n < 2) return 0;
        if (n == 2) return 1;
        ll inv_fact2 = pow_mod(fact(2), mod - 2);
        ll inv_fact_n_minus_2 = pow_mod(fact(n-2), mod - 2);
        return fact(n) * inv_fact2 % mod * inv_fact_n_minus_2 % mod;
    }
public:
    int countTrapezoids(vector<vector<int>>& points) {
        size_t max_size = 0;
        unordered_map<ll, vector<ll>> y_groups;
        for (auto& point: points) {
            int x = point[0], y = point[1];
            y_groups[y].push_back(x);
            max_size = max(max_size, y_groups[y].size());
        }
        dp.resize(max_size + 1, -1);

        unordered_map<ll, ll> choices;
        for (auto& [y, vec]: y_groups)
            choices[y] = combi2(vec.size());

        ll sum = 0;
        ll squaredSum = 0;
        for (auto& [y, choice]: choices) {
            sum = (sum + choice) % mod;
            squaredSum = (squaredSum + choice * choice % mod) % mod;
        }
        return ((sum * sum - squaredSum) % mod * pow_mod(2, mod - 2)) % mod;
    }
};