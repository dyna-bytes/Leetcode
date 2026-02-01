class Solution {
public:
    int minimumCost(vector<int>& nums) {
        multiset<int> st(nums.begin() + 1, nums.end());
        return nums[0] + *st.begin() + *next(st.begin());
    }
};