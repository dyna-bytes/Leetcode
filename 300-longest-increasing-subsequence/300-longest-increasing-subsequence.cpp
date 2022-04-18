class Solution {
public:
    
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        vector<int> dp(n, 0);
        int ret = 0;
        
        // dp[x] : nums[x]로 시작하는 LIS의 길이
        for(int i = n-1; i >= 0; i--){
            int max_dp = 0;
            for(int j = i + 1; j < n; j++){
                if(nums[i] < nums[j]){
                    max_dp = max(max_dp, dp[j]);
                }
            }
            dp[i] = 1 + max_dp;
            ret = max(ret, dp[i]);
        }
        return ret;
    }
    
};