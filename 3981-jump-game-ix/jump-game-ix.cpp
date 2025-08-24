#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto n: v) cout << n << "|"; \
    cout << endl; \
} while (0)

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int N = nums.size();
        vector<int> prefMax(N, 0);
        vector<int> suffMin(N, 0);
        prefMax[0] = nums[0];
        for (int i = 1; i < N; i++)
            prefMax[i] = max(prefMax[i-1], nums[i]);
        // debugVect(prefMax);

        suffMin[N-1] = nums[N-1];
        for (int i = N-2; i >= 0; i--)
            suffMin[i] = min(suffMin[i+1], nums[i]);
        // debugVect(suffMin);
        
        vector<int> dp(N, 0);
        dp[N-1] = prefMax[N-1];
        for (int i = N-2; i >= 0; i--) {
            dp[i] = prefMax[i];
            if (prefMax[i] > suffMin[i+1])
                dp[i] = max(dp[i], dp[i+1]);
        }
        return dp;
    }
};