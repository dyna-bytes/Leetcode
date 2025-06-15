class Solution {
    vector<int> dp;
public:
    int lengthOfLIS(vector<int>& nums) {
        dp.resize(nums.size(), -1);
        int ans = 0;
        for (int i = 0; i < nums.size(); i++)
            ans = max(ans, f(i, nums));
        return ans;
    }

    int f(int idx, vector<int>& nums) {
        if (idx >= nums.size()) return 0;

        int& ret = dp[idx];
        if (ret != -1) return ret;

        ret = 1;

        for (int i = idx + 1; i < nums.size(); i++) {
            if (nums[idx] < nums[i])
                ret = max(ret, 1 + f(i, nums));
        }

        return ret;
    }

};