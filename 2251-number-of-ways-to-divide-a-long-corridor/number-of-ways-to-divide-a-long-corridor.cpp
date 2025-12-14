class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    const ll mod = 1e9 + 7;
    bool invalidInput(string& corridor) {
        int seats = 0;
        for (char& ch: corridor)
            if (ch == 'S') seats++;

        if (seats & 1) return true;
        return false;
    }
public:
    int numberOfWays(string corridor) {
        int n = corridor.size();

        int seats = 0;
        vector<pll> segments;
        for (int i = 0; i < n; i++) {
            char& ch = corridor[i];
            if (ch == 'S') seats++;
            else continue;

            if (seats & 1) 
                segments.push_back({i, 0});
            else
                segments.back().second = i;
        }

        if (seats & 1) return 0;
        if (n == 1 || segments.size() == 0) return 0;
        if (segments.size() == 1) return 1;

        ll ret = 1;
        for (int i = 0; i < segments.size(); i++) {
            auto [s, e] = segments[i];
            if (i + 1 == segments.size()) continue;
            auto [ns, ne] = segments[i + 1];

            ret = ret * (ns - e) % mod;
        }
        return ret;
    }
};