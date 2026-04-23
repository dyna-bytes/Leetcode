class Solution {
    typedef long long ll;
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<ll> ret(n, 0);
        unordered_map<ll, vector<ll>> um;
        for (int i = 0; i < n; i++)
            um[nums[i]].push_back(i);

        for (auto& [_, vec]: um) {
            int k = vec.size();
            if (k < 2) continue;

            ll sum = accumulate(vec.begin(), vec.end(), 0LL);

            ll left_sum = 0;
            for (int i = 0; i < k; i++) {
                ll curr_idx = vec[i];
                ll right_sum = sum - left_sum - curr_idx;

                ll left_dist = (ll)i * curr_idx - left_sum;
                ll right_dist = right_sum - (ll)(k - 1 - i) * curr_idx;

                ret[curr_idx] = left_dist + right_dist;
                left_sum += curr_idx;
            }
        }
        return ret;
    }
};