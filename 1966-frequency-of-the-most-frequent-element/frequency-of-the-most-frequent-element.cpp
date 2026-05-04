class Solution {
    typedef long long ll;
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<ll> pref(n+1, 0);
        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        int ret = 0;
        for (int e = 0, s = 0; e < n; e++) {
            ll target = nums[e];
            while (s < e) {
                ll range_sum = pref[e+1] - pref[s];
                if (target * (e - s + 1) - range_sum > k)
                    s++;
                else
                    break;
            }
            ret = max(ret, e - s + 1);
        }
        return ret;
    }
};