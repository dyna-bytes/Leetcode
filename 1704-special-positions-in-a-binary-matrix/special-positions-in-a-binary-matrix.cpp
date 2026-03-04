#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int Y = mat.size();
        int X = mat[0].size();

        vector<int> rows(Y, 0);
        for (int y = 0; y < Y; ++y) {
            int sum = 0;
            for (int x = 0; x < X; ++x)
                sum += mat[y][x];
            rows[y] = sum;
        }

        vector<int> cols(X, 0);
        for (int x = 0; x < X; ++x) {
            int sum = 0;
            for (int y = 0; y < Y; ++y)
                sum += mat[y][x];
            cols[x] = sum;
        }

        int ret = 0;
        for (int y = 0; y < Y; ++y)
            for (int x = 0; x < X; ++x)
                if (mat[y][x] == 1 
                && rows[y] == 1 
                && cols[x] == 1)
                    ret++;
        return ret;
    }
};