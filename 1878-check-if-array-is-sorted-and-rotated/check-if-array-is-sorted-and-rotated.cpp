class Solution {
public:
    bool check(vector<int>& nums) {
        int p = 0;
        int n = nums.size();
        for (int i = 0; i < n-1; i++) {
            if (nums[i] > nums[i+1]) {
                p = i + 1;
                break;
            }
        }

        int max_x = nums[p];
        for (int i = 0; i < n; i++) {
            int x = nums[(i + p) % n];
            if (max_x > x) return false;
            max_x = max(max_x, x);
        }
        return true;
    }
};