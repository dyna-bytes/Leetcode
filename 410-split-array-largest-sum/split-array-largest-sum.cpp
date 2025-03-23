class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        if (nums.size() == 1) return nums[0];

        int l = 0;
        int r = 0;
        for (int n: nums) r += n;

        while (l + 1 < r) {
            int m = (l + r)/2;
            if (possible(m, nums, k)) r = m;
            else l = m;
        }
        return l + 1;
    }
    bool possible(int upperbound, vector<int>& nums, int K) {
        int k = 0;
        int sum = 0;
        for (int i = 0; i < nums.size(); k++) {
            if (k > K) return false;

            while (i < nums.size() && sum + nums[i] <= upperbound) {
                sum += nums[i];
                i++;
            }
            sum = 0;
        }

        return k <= K;
    }
};