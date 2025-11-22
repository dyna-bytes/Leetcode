class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int prev = 0;
        int next = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            next = (i == n - 1) ? INT_MIN : nums[i + 1];
            prev = (i == 0) ? INT_MIN : nums[i - 1];
            if (prev < nums[i] && nums[i] > next) return i;
        }
        return 0;
    }
};