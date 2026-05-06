#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
class Solution {
    int Y, X;
    void do_shift(vector<char>& row) {
        int s, m, e; // s: seg start, m: seg end, e: next seg start
        for (s = m = e = 0; e < X; ) {
            while (s < X && row[s] != '#') s++;
            if (s == X) break;

            m = s;
            while (m < X && row[m] == '#') m++;
            if (m == X) break;

            e = m;
            while (e < X && row[e] == '.') e++;

            int dist = e - m;
            if (dist)
                for (int i = m-1; i >= s; i--) {
                    row[i + dist] = row[i];
                    row[i] = '.';
                }

            if (e == X || row[e] == '*')
                s = e + 1;
            else
                s = s + dist;
        }
    }

    vector<vector<char>> rotate(vector<vector<char>>& grid) {
        vector<vector<char>> ret(X, vector<char>(Y));
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                ret[x][Y-1-y] = grid[y][x];
        return ret;
    }
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& grid) {
        Y = grid.size();
        X = grid[0].size();

        for (int y = 0; y < Y; y++) {
            debug(y);
            do_shift(grid[y]);
        }


        return rotate(grid);
    }
};