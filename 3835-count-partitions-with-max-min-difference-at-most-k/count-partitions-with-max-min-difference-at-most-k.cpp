class Solution {
    typedef long long ll;
    const ll mod = 1e9 + 7;
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> dp(n+1, 0);
        deque<int> maxq, minq;

        dp[0] = 1;

        ll curr_sum = 0;
        int s = 0;
        for (int e = 0; e < n; e++) {
            curr_sum = (curr_sum + dp[e]) % mod;

            while (maxq.size() && maxq.back() < nums[e])
                maxq.pop_back();
            while (minq.size() && minq.back() > nums[e])
                minq.pop_back();

            maxq.push_back(nums[e]);
            minq.push_back(nums[e]);

            while (maxq.front() - minq.front() > k) {
                if (maxq.front() == nums[s]) maxq.pop_front();
                if (minq.front() == nums[s]) minq.pop_front();
                curr_sum = (curr_sum - dp[s] + mod) % mod;
                s++;
            }

            dp[e + 1] = curr_sum;
        }
        return dp[n];
    }
};