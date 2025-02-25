class Solution {
public:
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    vector<vector<int>> visited;
    int Y, X;

    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    bool isDest(int y, int x) {
        return y == Y-1 && x == X-1;
    }

    int bfs(vector<vector<int>>& grid, int K) {
        queue<tuple<int, int, int, int>> Q; // {y, x, depth, step}
        Q.push({0, 0, 1, 0});
        visited[0][0] = 1;
        int steps = INT_MAX;

        while (!Q.empty()) {
            auto [y, x, depth, step] = Q.front(); Q.pop();

            if (isDest(y, x))
                steps = min(steps, step);

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (visited[ny][nx] && visited[ny][nx] <= depth) continue;
                if (grid[ny][nx] && depth > K) continue;
                
                int next_depth = depth + (grid[ny][nx] == 1);
                Q.push({ny, nx, next_depth, step + 1});
                visited[ny][nx] = next_depth;
            }
        }

        return steps == INT_MAX ? -1 : steps;
    }

    int shortestPath(vector<vector<int>>& grid, int k) {
        Y = grid.size();
        X = grid[0].size();
        visited.resize(Y, vector<int>(X, 0));

        return bfs(grid, k);
    }
};