class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        vector<int> psum(n+1, 0);
        for (int i = 0; i < n; i++) 
            psum[i + 1] = psum[i] + nums[i];

        int minlen = INT_MAX;
        for (int i = 0, j = 0; i <= n && j <= n; ) {
            int sum = psum[j] - psum[i];
            if (sum < target) j++;
            else {
                minlen = min(minlen, j - i);
                i++;
            }
        }

        if (minlen == INT_MAX) return 0;
        return minlen;
    }
};