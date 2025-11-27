typedef long long ll;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> prefix(n+1, 0);
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];

        vector<ll> arr(n - k + 1, 0);
        for (int i = k; i <= n; i++) 
            arr[i - k] = prefix[i] - prefix[i - k];
        
        ll maxsum = LONG_LONG_MIN;
        ll sum = 0;

        for (int i = 0; i < k; i++) {
            sum = 0;
            for (int j = i; j <= n - k; j += k) {
                sum += arr[j];
                maxsum = max(maxsum, sum);
                sum = max(sum, (ll)0);
            }
        }
        
        return maxsum;
    }
};