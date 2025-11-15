class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        
        int maxcnt = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) cnt++;
            else cnt = 0;
            maxcnt = max(maxcnt, cnt);
        }
        return maxcnt;
    }
};