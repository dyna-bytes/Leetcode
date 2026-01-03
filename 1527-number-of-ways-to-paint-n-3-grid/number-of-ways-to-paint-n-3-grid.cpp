class Solution {
    typedef long long ll;
    const ll mod = 1e9 + 7;
    enum color {
        R = 1,
        G = 2, 
        Y = 3,
    };
    #define GET_COLOR(row, pos) (row >> (2*(pos)) & 0x3)
    #define SET_COLOR(row, pos, color) (row | (color << (2*(pos))))

    vector<vector<ll>> dp;
    ll f(int y, int x, int prev_row, int curr_row) {
        if (y == 0) return 1; 

        if (x == 3) {
            return f(y - 1, 0, curr_row, 0);
        }

        ll& ret = dp[y][prev_row];
        if (x == 0 && ret != -1) return ret;
        ret = 0;

        int prev_x = x > 0 ? GET_COLOR(curr_row, x - 1) : 0;
        int prev_y = GET_COLOR(prev_row, x);

        for (int color = 1; color <= 3; color++) {
            if (color == prev_x || color == prev_y) continue;
            ret = (ret + f(y, x + 1, prev_row, SET_COLOR(curr_row, x, color))) % mod; 
        }
        return ret;
    }

public:
    int numOfWays(int n) {
        dp.resize(n + 1, 
            vector<ll>(64, -1));
        return f(n, 0, 0, 0);
    }
};