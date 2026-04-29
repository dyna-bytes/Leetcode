class Solution {
    typedef long long ll;
    int n;
    vector<vector<int>> grid;
    vector<vector<ll>> pref;

public:
    long long maximumScore(vector<vector<int>>& grid) {
        this->grid = grid;
        n = grid.size();
        pref.assign(n + 1, vector<ll>(n, 0));
        for (int y = 0; y < n; y++) 
            for (int x = 0; x < n; x++) 
                pref[y+1][x] = pref[y][x] + grid[y][x];
            
        // dp[h_1][h_2] : 이전 열(x-1)의 높이가 h_1, 그 이전 열(x-2)의 높이가 h_2일 때의 최댓값
        // x 단계의 결과를 담을 dp, x+1 단계의 결과를 들고 있는 next_dp
        vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
        vector<vector<ll>> next_dp(n + 1, vector<ll>(n + 1, 0));

        for (int x = n - 1; x >= 0; x--) {
            for (int h_1 = 0; h_1 <= n; h_1++) {
                vector<ll> pref_max1(n + 1, -1); // h <= h_1
                vector<ll> pref_max2(n + 1, -1); // h_1 < h <= M
                vector<ll> suff_max3(n + 1, -1); // M < h

                ll cur_max1 = -1, cur_max2 = -1;
                for (int h = 0; h <= n; h++) {
                    cur_max1 = max(cur_max1, next_dp[h][h_1] - pref[h][x]);
                    pref_max1[h] = cur_max1;
                    
                    cur_max2 = max(cur_max2, next_dp[h][h_1]);
                    pref_max2[h] = cur_max2;
                }
                ll cur_max3 = -1;
                for (int h = n; h >= 0; h--) {
                    ll val = next_dp[h][h_1];
                    if (x > 0) val += pref[h][x - 1];
                    cur_max3 = max(cur_max3, val);
                    suff_max3[h] = cur_max3;
                }

                for (int h_2 = 0; h_2 <= n; h_2++) {
                    int M = max(h_1, h_2);
                    ll ret = 0;

                    // 구간 1 (h <= h_1): 최댓값은 h_1 인덱스까지의 pref_max
                    ret = max(ret, pref[h_1][x] + pref_max1[h_1]);

                    // 구간 2 (h_1 < h <= M): 최댓값은 M 인덱스까지의 pref_max
                    if (M > h_1) {
                        ret = max(ret, pref_max2[M]);
                    }

                    // 구간 3 (h > M): 최댓값은 M+1 인덱스부터의 suff_max
                    if (M + 1 <= n) {
                        ll penalty = (x > 0) ? pref[M][x - 1] : 0;
                        ret = max(ret, -penalty + suff_max3[M + 1]);
                    }
                    dp[h_1][h_2] = ret;
                }
            }
            
            next_dp = dp; 
        }
        
        return dp[0][0]; 
    }
};