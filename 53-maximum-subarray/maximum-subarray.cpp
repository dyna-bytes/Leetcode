class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // cursum : 0보다 크거나 같은 값만 거르는 필터
        // subarr 의 합이 음수라면, 버리고 다시 시작하는게 항상 이득임
        int cursum = 0;
        int maxsum = nums[0];

        for (int num: nums) {
            cursum = max(cursum, 0);
            cursum += num;
            maxsum = max(maxsum, cursum);
        }
        return maxsum;
    }
};