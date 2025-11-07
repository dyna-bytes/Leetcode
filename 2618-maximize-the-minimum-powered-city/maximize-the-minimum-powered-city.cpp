class Solution {
    typedef long long ll;
    vector<int> stations;
    int n, r, k;

    vector<ll> init_powers;
    vector<ll> diff_powers;
    void fill_init() {
        vector<ll> psum(n+1, 0);
        for (int i = 0; i < n; i++) 
            psum[i+1] = psum[i] + stations[i];
        
        for (int i = 0; i < n; i++) 
            init_powers[i] = psum[min(n, i+r+1)] - psum[max(0, i-r)];
    }
    bool check(ll power_huddle) {
        diff_powers.clear();
        diff_powers.resize(n+1, 0);
        ll total_k_used = 0;
        ll diff_sum = 0;

        for (int i = 0; i < n; i++) {
            diff_sum += diff_powers[i];
            ll city_power = init_powers[i] + diff_sum;
            ll needed = 0;

            if (city_power < power_huddle)
                needed = power_huddle - city_power;

            total_k_used += needed;
            if (total_k_used > k) return false;

            diff_sum += needed;
            int end_effect_idx = min(n, i + 2*r + 1);
            diff_powers[end_effect_idx] -= needed;
        }
        return true;
    }
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        this->stations = stations;
        this->r = r;
        this->k = k;
        this->n = stations.size();
        init_powers.resize(n, 0);
        fill_init();

        ll lo = 0;
        ll hi = LONG_LONG_MAX;
        while (lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if (check(mid)) lo = mid;
            else hi = mid;
        }
        return lo;
    }
};