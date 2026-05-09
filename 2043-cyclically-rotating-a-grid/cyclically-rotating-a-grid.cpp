#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |" ; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#define debugVect2D(vv) do { \
    cout << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
    cout << endl; \
} while (0)

class Solution {
    int Y, X;
    void rotateLayer(vector<vector<int>>& grid, int lyr) {
        int buf = grid[lyr][lyr];
        for (int x = lyr + 1; x < X - lyr; x++) 
            grid[lyr][x - 1] = grid[lyr][x];
        for (int y = lyr + 1; y < Y - lyr; y++)
            grid[y - 1][X - lyr - 1] = grid[y][X - lyr - 1];
        for (int x = X - lyr - 2; x >= lyr; x--)
            grid[Y - lyr - 1][x + 1] = grid[Y - lyr - 1][x];
        for (int y = Y - lyr - 2; y >= lyr; y--)
            grid[y + 1][lyr] = grid[y][lyr];
        grid[lyr + 1][lyr] = buf;
    }
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        Y = grid.size();
        X = grid[0].size();

        for (int lyr = 0; lyr < min(Y, X)/2; lyr++) {
            int len = ((Y - 2*lyr - 1) + (X - 2*lyr - 1)) * 2;
            int t = k % len;
            while (t--)
                rotateLayer(grid, lyr);
        }
        return grid;
    }
};