class Solution {
public:
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

    int countBattleships(vector<vector<char>>& board) {
        int Y = board.size();
        int X = board[0].size();
        vector<vector<int>> visited(Y, vector<int>(X, false));

        auto inRange = [&](int y, int x) {
            return 0 <= y && y < Y && 0 <= x && x < X;
        };

        auto bfs = [&](int y, int x) {
            queue<pair<int, int>> Q;
            Q.push({y, x});
            visited[y][x] = true;

            while (!Q.empty()) {
                auto [y, x] = Q.front(); Q.pop();

                for (int d = 0; d < 4; d++) {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (!inRange(ny, nx)) continue;
                    if (visited[ny][nx]) continue;
                    if (board[ny][nx] == '.') continue;
                    Q.push({ny, nx});
                    visited[ny][nx] = true;
                }
            }
            return 1;
        };

        int components = 0;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (visited[y][x]) continue;
                if (board[y][x] == '.') continue;

                components += bfs(y, x);
            }
        }
        return components;
    }
};