class Solution {
    enum dirs {U, R, D, L};
    const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
    enum street_t {
        LR = 1,
        UD,
        LD,
        RD,
        LU,
        RU,
    };
    map<int, set<int>> ways = {
        {LR, {L, R}},
        {UD, {U, D}},
        {LD, {L, D}},
        {RD, {R, D}},
        {LU, {L, U}},
        {RU, {R, U}},
    };

    int Y, X;
    vector<vector<int>> grid, visited;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    int dfs(int y, int x) {
        if (y == Y-1 && x == X-1) return true;

        int ret = 0;
        street_t street = static_cast<street_t>(grid[y][x]);

        for (int dir: ways[street]) {
            int ny = y + dy[dir], nx = x + dx[dir];
            int opt_dir = (dir + 2) % 4;
            if (!inRange(ny, nx)) continue;
            if (ways[grid[ny][nx]].count(opt_dir) == 0) continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = true;

            ret += dfs(ny, nx);
        }
        return ret;
    }
    
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        Y = grid.size(), X = grid[0].size();
        this->grid = grid;
        visited.assign(Y, vector<int>(X, 0));

        visited[0][0] = true;
        return dfs(0, 0);
    }
};