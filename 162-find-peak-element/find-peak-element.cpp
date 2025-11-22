class Solution {
    typedef long long ll;
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int lo = -1, mid, hi = n;
        auto getnum = [&](int idx) {
            if (idx == -1 || idx == n) return LONG_LONG_MIN;
            return (ll)nums[idx];
        };

        while (true) {
            int mid = (lo + hi)/2;
            ll left = getnum(mid - 1);
            ll center = getnum(mid);
            ll right = getnum(mid + 1);
            if (left < center && center > right)
                return mid;
            else if (left < center && center < right)
                lo = mid;
            else if (left > center && center > right)
                hi = mid;
            else
                hi = mid;
        }

        return 0;
    }
};