class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int n = nums.size();
        int prev_i = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) continue;

            if (prev_i != -1)
                if (i - prev_i <= k) return false;
            prev_i = i;
        }

        return true;
    }
};