class Solution {
    unordered_map<int, int> visited;

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> stack;
        backtracking(0, nums, stack, ret);

        return ret;
    }
    void backtracking(int curr, vector<int>& nums, vector<int>& stack,
                      vector<vector<int>>& ret) {
        if (curr == nums.size()) {
            ret.push_back(stack);
            return;
        }

        stack.push_back(nums[curr]);
        backtracking(curr + 1, nums, stack, ret);
        stack.pop_back();

        backtracking(curr + 1, nums, stack, ret);
    }
};