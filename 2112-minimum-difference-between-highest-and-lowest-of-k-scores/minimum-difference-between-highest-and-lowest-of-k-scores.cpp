class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int min_dff = INT_MAX;
        for (int i = 0; i <= n - k; i++) {
            int lo = nums[i];
            int hi = nums[i + k - 1];
            min_dff = min(min_dff, hi - lo);
        }
        return min_dff;
    }
};