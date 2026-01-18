#define DBG
#ifdef DBG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is | " ; \
    for (auto e: v) cout << e << " | "; \
    cout << endl; \
} while (0)
#define debugVect2D(vv) do { \
    cout << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)
#else
#endif

class Solution {
    int Y;
    int X;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        Y = grid.size();
        X = grid[0].size();

        vector<vector<int>> horizons(Y, vector<int>(X, 0));
        vector<vector<int>> verticals(Y, vector<int>(X, 0));
        vector<vector<int>> diagonals(Y, vector<int>(X, 0));
        vector<vector<int>> antidiagonals(Y, vector<int>(X, 0));

        for (int y = 0; y < Y; y++) 
            for (int x = 0; x < X; x++)
                horizons[y][x] = (x > 0 ? horizons[y][x - 1] : 0) + grid[y][x];
        

        for (int x = 0; x < X; x++) 
            for (int y = 0; y < Y; y++)
                verticals[y][x] = (y > 0 ? verticals[y - 1][x] : 0) + grid[y][x];
       

        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                int prev = 0;
                if (inRange(y - 1, x - 1)) 
                    prev = diagonals[y-1][x-1];
                diagonals[y][x] = prev + grid[y][x];
            }
        }

        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                int prev = 0;
                if (inRange(y - 1, x + 1))
                    prev = antidiagonals[y - 1][x + 1];
                antidiagonals[y][x] = prev + grid[y][x];
            }
        }
        

        for (int k = min(Y, X); k > 1; k--) {
            for (int y = 0; y <= Y - k; y++) {
                for (int x = 0; x <= X - k; x++) {
                    int d = diagonals[y + k - 1][x + k - 1];
                    if (inRange(y - 1, x - 1)) d-= diagonals[y - 1][x - 1];

                    int ad = antidiagonals[y + k - 1][x];
                    if (inRange(y - 1, x + k)) ad -= antidiagonals[y - 1][x + k];

                    if (d != ad) continue;

                    bool match = true;
                    for (int i = 0; i < k; i++) {
                        int rowSum = horizons[y + i][x + k - 1] - (x > 0 ? horizons[y + i][x - 1] : 0);
                        int colSum = verticals[y + k - 1][x + i] - (y > 0 ? verticals[y - 1][x + i] : 0);
                        if (rowSum != d || colSum != d) {
                            match = false;
                            break;
                        }
                    }
                    if (match) return k;
                }
            }
        }

        return 1;
    }
};