class Solution {
    typedef long long ll;
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        vector<ll> pref(n+1, 0);
        for (int i = 0; i < n; i++)
            pref[i+1] = pref[i] + nums[i];

        ll minlen = INT_MAX;
        if (pref[n] % p == 0) return 0;

        // for (int s = 0, e; s < n; s++) {
        //     for (e = s + 1; e < n + 1; e++) {
        //         ll sum = pref[n] - (pref[e] - pref[s]);
        //         if (sum && (sum % p == 0))
        //             minlen = min(minlen, e - s);
        //     }
        // }

        unordered_map<ll, ll> hash;
        for (ll i = 0; i <= n; i++) {
            ll pref_s = (((pref[i] - pref[n]) % p) + p) % p;
            if (hash.count(pref_s) && !(i == n && hash[pref_s] == 0))
                minlen = min(minlen, i - hash[pref_s]);

            hash[pref[i] % p] = i;
        }
        if (minlen == INT_MAX) return -1;
        return minlen;
    }
};