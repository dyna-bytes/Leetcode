#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    const int INF = 1e9;
    typedef pair<int, int> pii;

public:
    int minCost(vector<vector<int>>& grid, int K) {
        int Y = grid.size(), X = grid[0].size();
        vector<vector<vector<int>>> dp(
            Y + 1, vector<vector<int>>(X + 1, vector<int>(K + 1, INF)));
        vector<pii> cells(Y * X);
        for (int y = 0, i = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                cells[i++] = {y, x};
        sort(cells.begin(), cells.end(), [&](pii& a, pii& b) {
            auto [ay, ax] = a;
            auto [by, bx] = b;
            return grid[ay][ax] > grid[by][bx];
        });

        dp[0][0][0] = 0;
        for (int k = 0; k <= K; k++) {
            if (k > 0) {
                int prev_k = INF;
                for (int i = 0; i < cells.size(); ) {
                    int j;
                    int batch_min = INF;

                    for (j = i; j < cells.size(); j++) {
                        auto [y1, x1] = cells[i];
                        auto [y2, x2] = cells[j];
                        if (grid[y1][x1] != grid[y2][x2]) break;

                        batch_min = min(batch_min, dp[y2][x2][k-1]);
                    }

                    prev_k = min(prev_k, batch_min);
                    for (int l = i; l < j; l++) {
                        auto [y, x] = cells[l];
                        dp[y][x][k] = min(dp[y][x][k], prev_k);
                    }

                    i = j;
                }
            }
            
            for (int y = 0; y < Y; y++) {
                for (int x = 0; x < X; x++) {
                    int prev_y = INF;
                    if (y > 0)
                        prev_y = dp[y - 1][x][k];

                    int prev_x = INF;
                    if (x > 0)
                        prev_x = dp[y][x - 1][k];

                    dp[y][x][k] =
                        min(dp[y][x][k], min(prev_y, prev_x) + grid[y][x]);
                }
            }
        }

        return dp[Y - 1][X - 1][K];
    }
};