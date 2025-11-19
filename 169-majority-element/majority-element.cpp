class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> um;
        int n = nums.size();
        for (int num: nums) {
            if (++um[num] >= (n/2 + (n&1)))
                return num;
        }
        return 0;
    }
};