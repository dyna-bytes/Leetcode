class Solution {
    unordered_map<int, vector<int>> um;
public:
    Solution(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            um[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        vector<int>& vec = um[target];
        int idx = rand() % um[target].size();

        return vec[idx];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */