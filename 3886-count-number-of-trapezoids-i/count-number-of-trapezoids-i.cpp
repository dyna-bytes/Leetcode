class Solution {
    typedef long long ll;
    const ll mod = 1e9 + 7;
    
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
    
    ll combi2(ll n) {
        if (n < 2) return 0;
        return n * (n - 1) / 2;
    }
public:
    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<ll, vector<ll>> y_groups;
        for (auto& point: points) {
            int x = point[0], y = point[1];
            y_groups[y].push_back(x);
        }

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