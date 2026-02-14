#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \ 
} while (0)

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        int Y = query_row + 1;
        int X = query_glass + 1;

        vector<vector<double>> glasses(Y + 1);
        for (int y = 0; y <= Y; y++)
            glasses[y].resize(y + 1);

        glasses[0][0] = poured;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < y + 1; x++) {
                if (glasses[y][x] <= 1) continue;

                double surplus = glasses[y][x] - 1;
                glasses[y][x] = 1;

                glasses[y+1][x] += surplus / 2;
                glasses[y+1][x+1] += surplus / 2;
            }
        }

        return min((double)1, glasses[Y - 1][X - 1]);
    }
};