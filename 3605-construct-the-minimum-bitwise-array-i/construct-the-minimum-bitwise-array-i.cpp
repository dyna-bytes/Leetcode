class Solution {
    int min_x(int n) {
        for (int x = 0; x < n; x++) {
            if ((x | (x + 1)) == n) return x;
        }
        return -1;
    }
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        for (int i = 0; i < n; i++)
            ans[i] = min_x(nums[i]);
        return ans;
    }
};