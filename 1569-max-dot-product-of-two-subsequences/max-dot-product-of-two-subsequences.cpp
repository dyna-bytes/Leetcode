class Solution {
    const int INF = 1e9;
    vector<int> nums1, nums2;
    vector<vector<int>> dp;

    int maxProduct(int i, int j) {
        if (i >= nums1.size() || j >= nums2.size()) return -INF;

        int& ret = dp[i][j];
        if (ret != -INF) return ret;

        ret = nums1[i] * nums2[j]; 
        ret = max(ret, maxProduct(i + 1, j));
        ret = max(ret, maxProduct(i, j + 1));
        ret = max(ret, maxProduct(i + 1, j + 1));
        ret = max(ret, nums1[i] * nums2[j] + maxProduct(i + 1, j + 1));
        return ret;
    }
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        this->nums1 = nums1;
        this->nums2 = nums2;
        dp.resize(nums1.size() + 1, vector<int>(nums2.size() + 1, -INF));

        return maxProduct(0, 0);
    }
};