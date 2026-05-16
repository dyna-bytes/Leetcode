class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        return f(nums, 0, nums.size()-1);
    }

    int f(vector<int>& nums, int s, int e) {
        if (s + 1 == e) return min(nums[s], nums[e]);

        if (nums[s] >= nums[e]) {
            int m = (s + e)/2;
            if (nums[m] > nums[e]) return f(nums, m, e);
            else if (nums[m] < nums[e]) return f(nums, s, m);
            else return min(f(nums, s, m), f(nums, m, e));
        } else
            return nums[s];
    }
};