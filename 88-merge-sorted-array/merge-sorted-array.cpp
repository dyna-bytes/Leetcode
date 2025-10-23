class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (m == 0) {
            nums1 = nums2;
            return;
        }
        if (n == 0)
            return;
        int a, b, c;

        for (a = m - 1, b = n - 1, c = m + n - 1; a >= 0 && b >= 0;) {
            if (nums1[a] > nums2[b])
                nums1[c--] = nums1[a--];
            else
                nums1[c--] = nums2[b--];
        }

        if (a <= 0) {
            for (; b >= 0;)
                nums1[c--] = nums2[b--];
        } else if (b <= 0) {
            for (; a >= 0;)
                nums1[c--] = nums1[a--];
        }
    }
};