class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // case 1. remove the two biggests.
        int ans1 = nums[n-3] - nums[0];

        // case 2. remove the two lowests.
        int ans2 = nums[n-1] - nums[2];

        // case 3. remove the biggest and th lowest.
        int ans3 = nums[n-2] - nums[1];

        return min({ans1, ans2, ans3});
    }
};