#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#define debugV2D(v) do { \
    std::cout << "[Debug] [\n"; \
    for(int y = 0; y < (v.size()); y++) { \
        std::cout << "  ["; \
        for(int x = 0; x < ((v[y].size())-1); x++) \
            std::cout << v[y][x] << "|"; \
        std::cout << v[y][(v[y].size())-1] << "]\n"; \
    } \
    std::cout << "]\n"; \
} while(0)

class Solution {
    int N;
    typedef pair<int, int> pii;
    typedef tuple<int, int, int> tiii;
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    vector<vector<int>> score_grid;
    vector<vector<int>> visited;
    bool inRange(int y, int x) {
        return 0 <= y && y < N && 0 <= x && x < N; 
    }
    void init_score_grid(vector<vector<int>>& grid) {
        queue<pii> q;
        visited.clear();
        visited.resize(N, vector<int>(N, false));

        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                if (grid[y][x]) {
                    score_grid[y][x] = 0;
                    q.push({y, x});
                    visited[y][x] = true;
                }

        while (q.size()) {
            auto [y, x] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (visited[ny][nx]) continue;
                q.push({ny, nx});
                visited[ny][nx] = true;
                score_grid[ny][nx] = score_grid[y][x] + 1;
            }
        }
    }
    bool canReach(int lb_safeness) {
        if (score_grid[0][0] < lb_safeness) return false;
        visited.clear();
        visited.resize(N, vector<int>(N, false));
             
        queue<pii> q;
        q.push({0, 0});
        visited[0][0] = true;

        while (q.size()) {
            auto [y, x] = q.front(); q.pop();
            if (y == N - 1 && x == N - 1) return true;
          
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (visited[ny][nx]) continue;
                if (score_grid[ny][nx] < lb_safeness) continue;
                 
                 visited[ny][nx] = true;
                 q.push({ny, nx});
            }
        }
        return false;
    }
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        N = grid.size();
        score_grid.resize(N, vector<int>(N, 9999));
        init_score_grid(grid);

        int l = 0, r = N * N + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (canReach(m)) l = m;
            else r = m;
        }
        return l;
    }
};