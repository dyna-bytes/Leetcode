class Solution {
    typedef long long ll;
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();
        vector<ll> psum(n + 1, 0);

        for (int i = 0; i < n; i++)
            psum[i+1] = psum[i] + nums[i];

        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            if (psum[i + 1] >= psum[n] - psum[i + 1])
                ans++;
        }

        return ans;
    }
};