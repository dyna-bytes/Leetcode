class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        vector<int> dp(3001);
        dp[0] = true;
        int sum = 0;
        for (int& stone: stones) {
            sum += stone;
            for (int possi_sum = sum; possi_sum >= stone; possi_sum--)
                dp[possi_sum] |= dp[possi_sum - stone];
        }

        for (int group_sum = sum/2; group_sum >= 0; group_sum--)
            if (dp[group_sum]) return (sum - group_sum) - group_sum;

        return 0;
    }
};