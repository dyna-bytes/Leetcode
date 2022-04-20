class Solution {
public:
    vector<long long> dp;
    int combinationSum4(vector<int>& nums, int target) {
        if(target == 0) return 0;
        dp.resize(target+1); // dp[n] := n을 만들 수 있는 경우의 수
        
        dp[0] = 1;
        for(int n = 1; n <= target; n++){
            for(int num: nums){
                if(n < num) continue;
                if(dp[n] + dp[n - num] < INT_MAX)
                    dp[n] += dp[n - num];
            }
        }
        return dp[target];
    }
    
};