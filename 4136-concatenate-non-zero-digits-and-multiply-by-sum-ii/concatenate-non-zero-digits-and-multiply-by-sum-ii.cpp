class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
    typedef long long ll;
    const ll mod = 1e9 + 7;
    vector<ll> pref;
    vector<ll> val, cnt;
    vector<ll> pow10;
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        pow10.assign(1e5 + 1, 0);
        pow10[0] = 1;
        for (int i = 0; i < pow10.size() - 1; ++i)
            pow10[i+1] = pow10[i] * 10 % mod;

        pref.assign(s.size() + 1, 0);
        for (int i = 0; i < s.size(); ++i)
            pref[i+1] = pref[i] + (s[i] - '0');

        val.assign(s.size() + 1, 0);
        cnt.assign(s.size() + 1, 0);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '0') {
                val[i+1] = val[i];
                cnt[i+1] = cnt[i];
            } else {
                val[i+1] = (val[i] * 10 + (s[i] - '0')) % mod;
                cnt[i+1] = cnt[i] + 1;
            }
        }

        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            auto& query = queries[i];
            int l = query[0], r = query[1] + 1;
            
            ll k = cnt[r] - cnt[l];
            ll x = (val[r] - val[l] * pow10[k] % mod + mod) % mod;
            ll sum = (pref[r] - pref[l]) % mod;
            ans[i] = x * sum % mod;
        }
        return ans;
    }
};