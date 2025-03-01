class Solution {
public:
    int N;
    vector<vector<int>> visited;
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    bool inRange(int y, int x) {
        return 0 <= y && y < N && 0 <= x && x < N;
    }

    int bfs(vector<vector<int>>& grid) {
        queue<tuple<int, int, int>> Q;
        Q.push({0, 0, grid[0][0]});
        visited[0][0] = grid[0][0];
        int min_t = INT_MAX;
        while (!Q.empty()) {
            auto [y, x, t] = Q.front(); Q.pop();

            if (y == N-1 && x == N-1) {
                min_t = min(min_t, t);
                continue;
            }

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (visited[ny][nx] != -1 && visited[ny][nx] <= t) continue;
                visited[ny][nx] = t;
                Q.push({ny, nx, max(t, grid[ny][nx])});
            }
        }

        return min_t;
    }
    
    int swimInWater(vector<vector<int>>& grid) {
        N = grid.size();
        visited.resize(N, vector<int>(N, -1));

        return bfs(grid);
    }
};