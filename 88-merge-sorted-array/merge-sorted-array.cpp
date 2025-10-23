class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> nums = nums1;

        int a, b, c;
        for (a = 0, b = 0, c = 0; a < m && b < n; ) {
            if (nums[a] < nums2[b])
                nums1[c++] = nums[a++];
            else
                nums1[c++] = nums2[b++];
        }

        if (a == m) {
            for ( ; b < n; )
                nums1[c++] = nums2[b++];
        } else if (b == n) {
            for ( ; a < m; )
                nums1[c++] = nums[a++];
        }
    }
};