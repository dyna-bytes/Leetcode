class Solution {
    int n;
    vector<int> nums;
    int sum;

    int F(int k) {
        int ret = 0;
        for (int i = 0; i < n; i++)
            ret += nums[i] * ((i + k) % n);
        return ret;
    }
    int diff(int i) { // F(i) - F(i-1) 
        return sum - n * nums[n-i];
    }
public:
    int maxRotateFunction(vector<int>& nums) {
        n = nums.size();
        this->nums = nums;
        sum = accumulate(nums.begin(), nums.end(), 0);

        int f = F(0);
        int ret = f;

        for (int i = 1; i < n; i++) {
            f += diff(i);
            ret = max(ret, f);
        }

        return ret;
    }
};