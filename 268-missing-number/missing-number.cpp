class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> um;
        for (int i = 0; i < n; i++) 
            um[nums[i]]++;

        for (int i = 0; i <= n; i++)
            if (um[i] == 0) return i;
        return -1;
    }
};