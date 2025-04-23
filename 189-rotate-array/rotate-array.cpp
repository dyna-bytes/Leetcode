class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;

        vector<int> ret(n, 0);
        int s = 0;
        for (int i = n - k; i < n; i++)
            ret[s] = nums[i], s++;

        for (int i = 0; i < n - k; i++)
            ret[s] = nums[i], s++;
        
        nums = ret;
    }
};