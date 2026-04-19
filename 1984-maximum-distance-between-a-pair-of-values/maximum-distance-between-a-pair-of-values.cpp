class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int l = i-1;
            int r = m;
            while (l + 1 < r) {
                int mid = (l + r)/2;
                if (nums2[mid] >= nums1[i]) l = mid;
                else r = mid;
            }

            if (r - 1 >= m) continue;
            ret = max(ret, r - 1 - i);
        }
        return ret;
    }
};