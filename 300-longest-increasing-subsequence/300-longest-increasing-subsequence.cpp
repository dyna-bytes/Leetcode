class Solution {
public:
    
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        vector<int> dp(1, INT_MIN);
        int ret = 0;
        
        for(int i = 0; i < n; i++){
            if(dp.back() < nums[i]){
                dp.push_back(nums[i]);
                ret++;
            }else{
                auto pos = lower_bound(dp.begin(), dp.end(), nums[i]);
                *pos = nums[i];
            }
        }
        return ret;
    }
    
};