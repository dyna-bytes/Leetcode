class Solution {
public:
    #define UNKNOWN -1
    vector<int> memo;
    int dp(int curr, const int N, const vector<int>& nums) {
        if (curr >= N-1) return 0;
        if (memo[curr] != UNKNOWN) return memo[curr];

        int min_jump = 1e9;
        for (int step = 1; step <= nums[curr]; step++) {
            min_jump = min(min_jump, 1 + dp(curr + step, N, nums));
        }
        return memo[curr] = min_jump;
    }

    int jump(vector<int>& nums) {
        int N = nums.size();
        memo.resize(N, UNKNOWN);
        return dp(0, N, nums);
    }
};