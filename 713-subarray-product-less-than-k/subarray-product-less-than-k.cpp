class Solution {
    typedef long long ll;
    int k, n;
    #define debug(x) cout << #x << " is " << x << endl;
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        n = nums.size();
    
        ll product = 1;
        int ans = 0;
        int s, e;
        for (s = 0, e = 0; e < n; e++) {
            product *= nums[e];
            while (product >= k)
                product /= nums[s++];
            ans += (e - s + 1);
        }
        
        return ans;
    }
};