#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    typedef long long ll;
    int n;
    vector<ll> prefix;
    map<pair<ll, ll>, ll> mp;
public:
    long long countStableSubarrays(vector<int>& a) {
        n = a.size();
        prefix.resize(n+1, 0);
        ll ret = 0;

        for (int i = 0; i < n; i++)
            prefix[i+1] = prefix[i] + a[i];

        // p[i] : sum(a[0], a[i-1])
        // p[r] - p[l+1] == a[r] == a[l]

        // for (int r = 1; r < n; r++) {
        //     for (int l = 0; l < r-1; l++) {
        //         if ((a[l] == a[r])
        //         && (prefix[r] - prefix[l+1] == a[r]))
        //             ret++;
        //     }
        // }

        for (int i = 1; i < n; i++) {
            ret += mp[{a[i], prefix[i] - a[i]}];
            mp[{a[i-1], prefix[i]}]++;
        }

        return ret;
    }
};