#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is | "; \
    for (auto e: v) cout << e << " | "; \
    cout << endl; \
} while (0)
#define debugVect2D(vv) do { \
    cout << #vv << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)

class Solution {
    typedef long long ll;
    const ll INF = 1e14;
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        vector<vector<ll>> dp(4, 
            vector<ll>(n + 1, -INF));

        // 0: Start Inc (len=1)
        // 1: Inc (len>=2) -> End of First Inc segment
        // 2: Dec (len>=2) -> End of Dec segment
        // 3: Inc (len>=2) -> End of Second Inc segment (Result Candidate)
        ll ans = -INF;
;
        for (int i = 0; i < n; ++i) {
            // 0단계: 언제든 새로 시작 가능
            dp[0][i] = nums[i]; 
            
            if (i > 0) {
                // 증가하는 경우
                if (nums[i] > nums[i-1]) {
                    dp[1][i] = nums[i] + max(dp[0][i-1], dp[1][i-1]); // State 0 or 1 -> 1
                    dp[3][i] = nums[i] + max(dp[2][i-1], dp[3][i-1]); // State 2 or 3 -> 3
                }
                // 감소하는 경우
                if (nums[i] < nums[i-1]) {
                    dp[2][i] = nums[i] + max(dp[1][i-1], dp[2][i-1]); // State 1 or 2 -> 2
                }
            }
            
            // 최종 답 갱신: dp[3][i] 중 최대값
            ans = max(ans, dp[3][i]);
        }
        return ans;
    }
};