// #define DBG
#ifdef DBG
#define debug(x) cout << __func__ << " " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << __func__ << " " << #v << " |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#define debugVect2D(vv) do { \
    cout << __func__ << " " << #vv << endl; \
    for (auto v: vv) debugVect(v); \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#define debugVect2D(vv)
#endif

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int sz) {
        parent.resize(sz, -1);
    }

    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }

    int merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;

        parent[u] += parent[v];
        parent[v] = u;
        return true;
    }
};

class Solution {
    typedef pair<int, int> pii;
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    int Y, X;
    vector<vector<int>> grid;
    bool inRange(int y, int x) {
        return 1 <= y && y < Y && 1 <= x && x < X;
    }
    int map(const pii& p) {
        int y = p.first, x = p.second;
        return y * (X + 1) + x;
    }
    
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        Y = row + 1;
        X = col + 1;

        grid.resize(Y + 1, vector<int>(X + 1, 0));
        UnionFind uf((Y + 1) * (X + 1));
        
        int left = map({1, 0});
        grid[1][0] = uf.find(left);
        for (int y = 2; y < Y; y++) {
            uf.merge(left, map({y, 0}));
            grid[y][0] = uf.find(map({y, 0}));
        }

        int right = map({1, X});
        grid[1][X] = uf.find(right);
        for (int y = 2; y < Y; y++) {
            uf.merge(right, map({y, X}));
            grid[y][X] = uf.find(map({y, X}));
        }

        for (int day = 0; day < cells.size(); day++) {
            int cy = cells[day][0], cx = cells[day][1];
            grid[cy][cx] = uf.find(map({cy, cx}));
            for (int y = cy - 1; y <= cy + 1; y++) {
                if (grid[y][cx - 1])
                    uf.merge(grid[y][cx - 1], grid[cy][cx]);
                if (grid[y][cx + 1])
                    uf.merge(grid[y][cx + 1], grid[cy][cx]);
            }

            if (grid[cy - 1][cx])
                uf.merge(grid[cy - 1][cx], grid[cy][cx]);
            if (grid[cy + 1][cx])
                uf.merge(grid[cy + 1][cx], grid[cy][cx]);
            
            debugVect2D(grid);
            debug(uf.find(left));
            debug(uf.find(right));

            if (uf.find(left) == uf.find(right))
                return day;
        }
        return cells.size() - 1;
    }
};