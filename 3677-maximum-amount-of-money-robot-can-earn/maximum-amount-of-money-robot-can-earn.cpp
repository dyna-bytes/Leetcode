#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    const int dy[2] = {1, 0};
    const int dx[2] = {0, 1};
    const int INF = 1e9 + 7;    

    int Y, X;
    vector<vector<int>> coins;
    vector<vector<vector<int>>> dp;

    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    int f(int y, int x, int counts) {
        if (y == Y - 1 && x == X - 1) {
            if (coins[y][x] <= 0 && counts > 0) return 0;
            return coins[y][x];
        }

        int& ret = dp[y][x][counts];
        if (ret != -INF) return ret;
        
        if (coins[y][x] >= 0) {
            for (int d = 0; d < 2; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                ret = max(ret, coins[y][x] + f(ny, nx, counts));
            }
        } else {
            if (counts > 0) {
                for (int d = 0; d < 2; d++) {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (!inRange(ny, nx)) continue;
                    ret = max(ret, f(ny, nx, counts - 1));
                }
            }

            for (int d = 0; d < 2; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                ret = max(ret, coins[y][x] + f(ny, nx, counts));
            }
        }
        return ret;
    }
public:
    int maximumAmount(vector<vector<int>>& coins) {
        this->coins = coins;
        Y = coins.size(), X = coins[0].size();
        dp.resize(Y + 1, vector<vector<int>>(X + 1, vector<int>(3, -INF)));

        return f(0, 0, 2);
    }
};