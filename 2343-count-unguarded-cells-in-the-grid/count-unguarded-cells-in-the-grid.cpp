#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    typedef pair<int, int> pii;
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    #define WATCHED 1
    #define WALL 2
    #define GUARD 3
    int Y, X;
    vector<vector<int>> visited;
    queue<pii> q;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        Y = m, X = n;
        visited.resize(Y, vector<int>(X, false));

        for (auto& wall: walls) {
            int y = wall[0], x = wall[1];
            visited[y][x] = WALL;
        }

        for (auto& guard: guards) {
            int y = guard[0], x = guard[1];
            q.push({y, x});
            visited[y][x] = GUARD;
        }


        int guarded = 0;
        while (q.size()) {
            auto [y, x] = q.front(); q.pop();

            for (int d = 0; d < 4; d++) {
                for (int ny, nx, i = 1; ; i++) {
                    ny = y + dy[d] * i;
                    nx = x + dx[d] * i;
                    if (!inRange(ny, nx)) break;
                    if (visited[ny][nx] == WALL || visited[ny][nx] == GUARD) break;

                    if (!visited[ny][nx]) guarded++;
                    visited[ny][nx] = WATCHED;
                }
            }
        }

        return Y*X - guarded - guards.size() - walls.size();
    }
};