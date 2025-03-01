class Solution {
public:
    typedef long long ll;
    const int mod = 1e9 + 7;
    vector<vector<vector<ll>>> memo;

    int dp(int N, int L, int A) {
        // base case
        memo[1][1][0] = 1, memo[1][0][1] = 1, memo[1][0][0] = 1; // L, A, P

        for (int n = 1; n < N; n++) {
            // for L == 2
            {
                // for A == 1
                memo[n+1][2][1] = memo[n][1][1]; // use L
                // for A == 0
                memo[n+1][2][0] = memo[n][1][0]; // use L
            }

            // for L == 1
            {
                // for A == 1
                memo[n+1][1][1] = memo[n][0][1]; // use L
                // for A == 0
                memo[n+1][1][0] = memo[n][0][0]; // use L or A or P
            }

            // for L == 0
            {
                // for A == 1
                ll& m = memo[n+1][0][1];
                m = (m + memo[n][2][0]) % mod; // use A from 2 L
                m = (m + memo[n][1][0]) % mod; // use A from 1 L
                m = (m + memo[n][0][0]) % mod; // use A from 0 L
                m = (m + memo[n][2][1]) % mod; // use P from 2 L
                m = (m + memo[n][1][1]) % mod; // use P from 1 L
                m = (m + memo[n][0][1]) % mod; // use P from 0 L

                // for A == 0
                ll& mm = memo[n+1][0][0];
                mm = (mm + memo[n][2][0]) % mod; // use P from 2 L
                mm = (mm + memo[n][1][0]) % mod; // use P from 1 L
                mm = (mm + memo[n][0][0]) % mod; // use P from 0 L
            }
        }

        ll ret = 0;
        for (int l = 0; l < 3; l++)
            for (int a = 0; a < 2; a++)
                ret = (ret + memo[N][l][a]) % mod;
        return ret;
    }

    int checkRecord(int n) {
        memo.resize(n + 1, vector<vector<ll>>(3, vector<ll>(2, 0)));

        return dp(n, 0, 0);
    }
};