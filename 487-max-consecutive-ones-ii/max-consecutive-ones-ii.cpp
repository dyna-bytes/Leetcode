class Solution {
    vector<int> nums;
    vector<vector<int>> dp;
    // 정의: 인덱스 'curr'에서부터 시작하는 연속된 1의 최대 길이
    int f(int curr, int chance) {
        if (curr >= nums.size()) return 0;

        int& ret = dp[curr][chance];
        if (ret != -1) return ret;

        if (nums[curr]) ret = 1 + f(curr + 1, chance);
        else {
            if (chance) ret = 1 + f(curr + 1, 0);
            else ret = 0;
        }
        return ret;
    }
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        this->nums = nums;
        int n = nums.size();
        dp.resize(n + 1, vector<int>(2, -1));

        int ret = 0;
        for (int i = 0; i < n; i++)        
            ret = max(ret, f(i, 1));
        return ret;
    }
};