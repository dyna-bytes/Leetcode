class Solution {
public:
    int racecar(int target) {
#define MAX_N 20005
typedef long long ll;
        ll dp[MAX_N];
        fill(dp, dp + MAX_N, INT_MAX);

        for (int t = 1; t <= target; t++) {
            for (int n = 0; ; n++) {
                int p = (1 << n) - 1;
                if (p >= 2*t) break;

                if (p == t)
                    dp[t] = n;
                else if (p > t)
                    dp[t] = min(dp[t], n + dp[p - t] + 1);
                    // dp[p - q] = dp[p] + dp[q] + 1
                else {
                    for (int m = 0; m < n; m++) {
                        int q = (1 << m) - 1;
                        dp[t] = min(dp[t], n + m + 2 + dp[t - p + q]);
                        // dp[p - q + r] = dp[p] + dp[q] + 1 + dp[r] + 1
                    }
                }
            }
        }

        return dp[target];
    }
};