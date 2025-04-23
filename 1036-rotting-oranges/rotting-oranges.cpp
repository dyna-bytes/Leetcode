class Solution {
    typedef pair<int, int> pii;
    int dy[4] = {-1, 1, 0, 0};
    int dx[4] = {0, 0, -1, 1};
    int Y, X;
    int inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {
        Y = grid.size();
        X = grid[0].size();
        return bfs(grid);
    }

    int bfs(vector<vector<int>>& grid) {
        int total = 0;
        int rotten = 0;
        queue<pii> q;

        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++) {
                if (grid[y][x] == 2) {
                    q.push({y, x});
                    rotten++;
                }

                if (grid[y][x]) total++;
            }
        
        int step = -1;
        
        for (; !q.empty(); step++) {
            int qsize = q.size();
            for (int i = 0; i < qsize; i++) {
                auto [y, x] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (!inRange(ny, nx)) continue;
                    if (grid[ny][nx] == 2) continue;
                    if (grid[ny][nx] == 0) continue;

                    grid[ny][nx] = 2;
                    q.push({ny, nx});
                    rotten++;
                }
            }
        }

        if (rotten == total) return max(step, 0);
        return -1;
    }
};