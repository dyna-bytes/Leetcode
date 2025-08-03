class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if (n <= 4) return 0;

        sort(nums.begin(), nums.end());

        int ret = abs(nums[0] - nums[n - 4]);
        ret = min(ret, abs(nums[1] - nums[n - 3]));
        ret = min(ret, abs(nums[2] - nums[n - 2]));
        ret = min(ret, abs(nums[3] - nums[n - 1]));
        return ret;
    }
};