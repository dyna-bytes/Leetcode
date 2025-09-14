#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e:v) cout << e << "|"; \
    cout << endl; \
} while (0)
class Solution {
    typedef long long ll;
    const ll MOD = 1e9 + 7;
    vector<vector<vector<ll>>> dp; // dp[n][p][c]: [n, e) 까지 stable subseq 개수
    int f(int n, int prev_parity, int count, vector<int>& nums) {
        if (n == nums.size()) {
            return 0;
        }

        // ll ret = 0;
        ll& ret = dp[n][prev_parity][count];
        if (ret != -1) return ret;

        bool curr_parity = nums[n] & 1;
        ret = f(n+1, prev_parity, count, nums); // skip current num

        if (curr_parity == prev_parity && count == 2) {
            // cannot choose current n
        } else {
            // choose current n
            int new_count = (curr_parity == prev_parity) ? count + 1 : 1;
            // expend with same parity (count + 1)
            // or, expend with different parity (reset count = 1)
            ret += (1 + f(n+1, curr_parity, new_count, nums));
            // choosing current n -> +1 경우의 수
            ret %= MOD;
        }
        
        return ret;
    }
public:
    int countStableSubsequences(vector<int>& nums) {
        dp.resize(nums.size() + 1, vector<vector<ll>>(2, vector<ll>(3, -1)));
        return f(0, nums[0] & 1, 0, nums);
        // initial_parity = (nums[0] & 1)
        // 1 + f(n+1, nums[0]'s parity, count = 1, nums)
    }
};