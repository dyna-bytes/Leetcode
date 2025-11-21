class Solution {
    typedef long long ll;
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        
        set<vector<ll>> st;

        int p, q, r, s;
        for (p = 0; p < n - 3; p++) {
            for (q = p + 1; q < n - 2; q++) {
                for (r = q + 1, s = n - 1; r < s; ) {
                    ll sum = (ll)nums[p] + nums[q] + nums[r] + nums[s];
                    if (sum < (ll)target) r++;
                    else if (sum > (ll)target) s--;
                    else if (st.count({ nums[p], nums[q], nums[r], nums[s] }))
                        r++, s--;
                    else {
                        ret.push_back({ nums[p], nums[q], nums[r], nums[s] });
                        st.insert({ nums[p], nums[q], nums[r], nums[s] });
                        r++, s--;
                    }
                }
            }
        }
        return ret;
    }
};