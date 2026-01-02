class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        int n = nums.size() / 2;
        int count[10000 + 1] = {};

        for (int i = 0; i < 2*n; i++) {
            if (++count[nums[i]] > 1) return nums[i];
        }
        return 0;
    }
};