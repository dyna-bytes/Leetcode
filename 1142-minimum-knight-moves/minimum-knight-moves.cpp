#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef pair<int, int> pii;
    const int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    const int SIZE = 1000;
public:
    int minKnightMoves(int X, int Y) {
        queue<pii> q;
        vector<vector<int>> visited(SIZE, vector<int>(SIZE, 0));
        auto mark_visited = [&](int y, int x) {
            y += 500, x += 500;
            visited[y][x] = true;
        };
        auto is_visited = [&](int y, int x) {
            y += 500, x += 500;
            return visited[y][x];
        };
        
        q.push({0, 0});
        mark_visited(0, 0);

        int level = 0;
        while (q.size()) {
            int qsize = q.size();
            for (int i = 0; i < qsize; i++) {
                auto [y, x] = q.front(); q.pop();
                if (y == Y && x == X) return level;

                for (int d = 0; d < 8; d++) {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (is_visited(ny, nx)) continue;
                    mark_visited(ny, nx);
                    q.push({ny, nx});
                }
            }
            
            level++;
        }
        return -1;
    }
};