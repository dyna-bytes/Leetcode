class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        if (k == 0) return (nums1 == nums2) ? 0 : -1;

        int n = nums1.size();
        long long pos_diff = 0;
        long long neg_diff = 0;
        for (int i = 0; i < n; i++) {
            int diff = nums1[i] - nums2[i];
            if (diff % k) return -1;

            if (diff > 0) pos_diff += diff;
            else neg_diff += diff;
        }

        if (pos_diff + neg_diff) return -1;
        return pos_diff / k;
    }
};