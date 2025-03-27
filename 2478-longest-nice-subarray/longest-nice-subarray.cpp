class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int maxLen = 1;
        for (int s = 0, e = 0; s < nums.size() && e < nums.size(); ) {
            e = s + 1;
            int orSum = nums[s];
            while ((e < nums.size()) && !(orSum & nums[e])) {
                maxLen = max(maxLen, e - s + 1);
                orSum |= nums[e];
                e++;
            }

            if (e == nums.size()) break;
            
            while (s <= e && (orSum & nums[e])) {
                orSum &= (~nums[s]);
                s++;
            }
        }
        return maxLen;
    }
};