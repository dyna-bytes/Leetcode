#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    int k;
    vector<vector<int>> grid;
    int Y, X;
    const int dy[2] = {0, 1}, dx[2] = {1, 0}; // right, down
    vector<vector<vector<int>>> dp;
    
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    int f(int y, int x, int cost_sum) {
        int cost = !!grid[y][x];
        int score = grid[y][x];

        if (cost_sum + cost > k) return -1; 
        if (y == Y - 1 && x == X - 1) return grid[Y-1][X-1];

        cost_sum += cost;

        int& ret = dp[y][x][cost_sum];
        if (ret != -2) return ret;
        ret = -1;
        for (int d = 0; d < 2; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            
            int next_cost = !!grid[ny][nx];
            if (cost_sum + next_cost > k) continue;
            
            int next_score = f(ny, nx, cost_sum);
            if (next_score == -1) continue;
            
            ret = max(ret, score + next_score);
        }
        return ret;
    }
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        this->k = k;
        this->grid = grid;
        Y = grid.size(), X = grid[0].size();
        dp.resize(Y, vector<vector<int>>(X, vector<int>(k + 1, -2)));
        
        int ret = f(0, 0, 0);
        if (ret <= -1) return -1;
        return ret;
    }
};