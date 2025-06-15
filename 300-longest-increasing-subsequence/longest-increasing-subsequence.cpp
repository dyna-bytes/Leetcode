class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> lastValOfLen; // 길이가 i인 부분 증가 수열의 마지막 항 중 최소값

        for (int i = 0; i < nums.size(); i++) {
            if (!lastValOfLen.size() || lastValOfLen.back() < nums[i])
                lastValOfLen.push_back(nums[i]);
            else if (lastValOfLen.front() > nums[i])
                lastValOfLen[0] = nums[i];
            else {
                auto it = lower_bound(lastValOfLen.begin(),
                    lastValOfLen.end(), nums[i]);
                *it = nums[i];
            }
        }

        return lastValOfLen.size();
    }
};