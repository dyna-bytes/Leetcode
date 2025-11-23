class Solution {
    int Y, X;
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    typedef pair<int, int> pii;
    vector<vector<int>> board;
    vector<vector<vector<int>>> visited;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
    bool touchWall(int y, int x, int d) {
        if (!inRange(y, x)) return false;
        
        int ny = y + dy[d], nx = x + dx[d];
        return (!inRange(ny, nx) || board[ny][nx]);
    }
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest) {
        Y = maze.size(), X = maze[0].size();
        this->board = maze;
        int sy = start[0], sx = start[1];
        int ey = dest[0], ex = dest[1];
        visited.resize(Y + 1, vector<vector<int>>(X + 1, vector<int>(4, 0)));

        queue<pair<pii, int>> q;
        for (int d = 0; d < 4; d++) {
            q.push({{sy, sx}, d});
            visited[sy][sx][d] = true;
        }

        while (q.size()) {
            auto [pos, dir] = q.front(); q.pop();
            auto [y, x] = pos;

            if (y == ey && x == ex && touchWall(y, x, dir)) return true;

            if (touchWall(y, x, dir)) {
                for (int d = 0; d < 4; d++) {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (!inRange(ny, nx)) continue;
                    if (board[ny][nx]) continue;
                    if (visited[ny][nx][d]) continue;
                    visited[ny][nx][d] = true;
                    q.push({{ny, nx}, d});
                }
            } else {
                int ny = y + dy[dir], nx = x + dx[dir];
                if (!inRange(ny, nx)) continue;
                if (board[ny][nx]) continue;
                if (visited[ny][nx][dir]) continue;
                visited[ny][nx][dir] = true;
                q.push({{ny, nx}, dir});
            }
        }
        return false;
    }
};