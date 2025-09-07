class Solution {
public:
    int minOperations(vector<int>& nums) {
        int minn = *min_element(nums.begin(), nums.end());
        int maxn = *max_element(nums.begin(), nums.end());

        if (minn == maxn) return 0;
        return 1;
    }
};