class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        if (nums.size() == 0) return {{lower, upper}};
        vector<vector<int>> ret;

        int front = nums.front();
        if (lower != front)
            ret.push_back({lower, front - 1});

        for (int i = 0; i < nums.size() - 1; i++) {
            int curr = nums[i];
            int next = nums[i + 1];
            if (curr + 1 != next)
                ret.push_back({curr + 1, next - 1});
        }

        int back = nums.back();
        if (back != upper)
            ret.push_back({back + 1, upper});
        return ret;
    }
};