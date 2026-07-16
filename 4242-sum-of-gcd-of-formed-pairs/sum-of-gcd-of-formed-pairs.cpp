class Solution {
    typedef long long ll;
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> mx(n, 0);
        mx[0] = nums[0];
        for (int i = 1; i < n; ++i)
            mx[i] = max(mx[i-1], nums[i]);

        vector<ll> prefGcd(n, 0);
        for (int i = 0; i < n; ++i)
            prefGcd[i] = __gcd(nums[i], mx[i]);
        
        sort(prefGcd.begin(), prefGcd.end());
        ll sum = 0;
        for (int i = 0; i < n/2; ++i)
            sum += __gcd(prefGcd[i], prefGcd[n - 1 - i]);
        return sum;
    }
};