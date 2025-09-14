#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e:v) cout << e << "|"; \
    cout << endl; \ 
} while (0)

/*
 * DP 테이블 정의:
 * boolean dp[s] : nums 의 원소들을 사용하여 합계 s을 만드는 것이 가능한지 여부. '현재까지 만들 수 있는 합'들의 집합.
 * 
 * 풀이 로직:
 * '현재까지 만들 수 있는 합' 들의 집합을 확장.
 * 
 * dp[x] ~ dp[k] 중 가능한게 있다면 (참인 element 가 하나라도 있다면),
 * 남은 nums 중 x 로 cap 되는 애들 (nums > x) 로 만들 수 있는 capped_sum = capped_cnt * x 을 구해
 * s = k - capped_sum 인 s 가 [x, k] 에 존재하는지 판별하면 된다.
 * dp[s + capped_sum] = dp[k] = true, if dp[s] = true.
 * 
 * Base case:
 * dp[0] = true
 * 
 * 점화식:
 * dp[s + x] = true, if dp[s] is true, for s in [0, k - x], for x in [1, n]
*/

class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        int N = nums.size();
        vector<bool> ret(N);
        vector<int> dp(k + 1); // dp[sum] = true/false
        sort(nums.begin(), nums.end());
        dp[0] = true;

        int i = 0;
        for (int x = 1; x <= N; x++) {
            for ( ; i < N && nums[i] == x; i++) {
                for (int s = k; s >= x; s--)
                    if (dp[s - x])
                        dp[s] = true;
            }

            int capped_count = N - i;
            bool is_possible = false;

            for (int j = 0; j <= capped_count;j++) {
                int capped_sum = j * x;
                if (k >= capped_sum && dp[k - capped_sum]) {
                    is_possible = true;
                    break;
                }
            }

            ret[x - 1] = is_possible;
        }

        return ret;
    }
};