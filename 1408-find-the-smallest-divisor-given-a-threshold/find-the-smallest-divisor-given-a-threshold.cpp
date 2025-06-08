#define debug(x) cout << #x << " is " << x << endl;

class Solution {
#define div(n, x) int(n/x) + bool(n % x)
    bool cond(int divisor, vector<int>& nums, int threshold) {
        int sum = 0;
        for (int n: nums)
            sum += div(n, divisor);
        
        return sum <= threshold;
    }
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int l = 1;
        int r = 1 + *max_element(nums.begin(), nums.end());
        
        while (l + 1 < r) {
            int m = (l + r)/2;
            if (cond(m, nums, threshold))
                r = m;
            else
                l = m;
        }
        
        if (cond(l, nums, threshold)) return l;
        return l + 1;
    }
};