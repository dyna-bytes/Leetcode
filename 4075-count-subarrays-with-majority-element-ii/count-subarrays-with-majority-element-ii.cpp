class Solution {
    typedef long long ll;
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<ll, ll> prefsum_freq;
        prefsum_freq[0] = 1;
        ll prefsum = 0;

        ll ret = 0, prefsum_accm = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                prefsum_accm += prefsum_freq[prefsum];
                ++prefsum;
                ++prefsum_freq[prefsum];
            } else {
                --prefsum;
                prefsum_accm -= prefsum_freq[prefsum];
                ++prefsum_freq[prefsum];
            }
            ret += prefsum_accm;
        }
        return ret;
    }
};