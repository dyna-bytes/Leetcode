class Solution {
    typedef long long ll;
    const ll mod = 1e9 + 7;
public:
    int numSub(string s) {
        int n = s.size();

        ll ans = 0;
        ll cnt = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') cnt++;
            else {
                ans = (ans + cnt * (cnt + 1) / 2) % mod;
                cnt = 0;
            }
        }
        ans = (ans + cnt * (cnt + 1) / 2) % mod;

        return ans;
    }
};