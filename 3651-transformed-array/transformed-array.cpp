class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);

        for (int i = 0; i < n; i++) {
            int step = (i + nums[i]) % n;
            if (step < 0) step = (step + n) % n;
            res[i] = nums[step];
        }
        return res;
    }
};