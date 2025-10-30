class Solution {
    typedef pair<int, int> pii;
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> psum(n+1, vector<int>(2, 0));
        for (int i = 0; i < n; i++) {
            psum[i+1][0] = psum[i][0] + (nums[i] == 0);
            psum[i+1][1] = psum[i][1] + (nums[i] == 1);
        }

        int max_len = 0;
        unordered_map<int, int> seen_01;
        seen_01[0] = 0;

        for (int e = 1; e <= n; e++) {
            int diff_01 = psum[e][1] - psum[e][0];
            if (seen_01.count(diff_01))
                max_len = max(max_len, e - seen_01[diff_01]);
            else
                seen_01[diff_01] = e;
        }
        return max_len;
    }
};