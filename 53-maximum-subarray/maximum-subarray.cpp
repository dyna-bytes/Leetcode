/*
divide and conquer

Anser in left, right or middle.
middle takes O(N)
*/
#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    vector<int> nums;
    // [l, r)
    int f(int l, int r) {
        if (l >= r) return INT_MIN;
        if (l + 1 == r) return nums[l];
        int ret;

        int m = (l + r)/2;
        int max_sum = INT_MIN;
        int lhalf_sum = 0;
        for (int i = m; i >= l; i--) {
            lhalf_sum += nums[i];
            max_sum = max(max_sum, lhalf_sum);
        }

        ret = max_sum;
        max_sum = 0;

        int rhalf_sum = 0;
        for (int i = m + 1; i < r; i++) {
            rhalf_sum += nums[i];
            max_sum = max(max_sum, rhalf_sum);
        }

        ret += max_sum;

        return max({ret, f(l, m), f(m, r)});
    }
public:
    int maxSubArray(vector<int>& nums) {
        this->nums = nums;
        return f(0, nums.size());
    }
};