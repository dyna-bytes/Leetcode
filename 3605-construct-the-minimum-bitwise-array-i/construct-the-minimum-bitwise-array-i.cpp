#define debug(x) cout << #x << " is " << x << endl; 

class Solution {
    int min_x(int n) {
        for (int i = 0; i < 32; i++) {
            int x = 1 << i;
            if (n & x) {
                for (int j = i + 1; j < 32; j++) {
                    int y = 1 << j;
                    if ((n & y) == 0) {
                        --j;
                        int ret = n ^ (1 << j);
                        if (ret == 0) return -1;
                        return ret;
                    }
                }
            }
        }
        return -1;
    }
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        for (int i = 0; i < n; i++)
            ans[i] = min_x(nums[i]);
        return ans;
    }
};