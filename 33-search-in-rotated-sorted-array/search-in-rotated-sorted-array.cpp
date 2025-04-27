class Solution {
    int findPivot(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < r && nums[l] > nums[r]) {
            int m = (l + r) / 2;
            if (nums[l] < nums[m])
                l = m;
            else
                r = m;
        }
        return max(n - 1 - l, 0);
    }
    int searchTargetIndex(int s, int e, vector<int>& nums, int target) {
        while (s + 1 < e) {
            int m = (s + e) / 2;
            if (target < nums[m])
                e = m;
            else
                s = m;
        }
        return s;
    }

public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 1) {
            if (target == nums[0]) return 0;
            return -1;
        }

        int k = findPivot(nums);
        int s, e;
        if (nums[0] <= target && target <= nums[n - 1 - k]) {
            s = 0, e = n - k;
        } else if (nums[n - k] <= target && target <= nums[n - 1]) {
            s = n - k, e = n;
        } else
            return -1;

        int idx = searchTargetIndex(s, e, nums, target);
        if (nums[idx] != target)
            return -1;
        return idx;
    }
};