class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        auto shift = [](vector<vector<int>>& mat) -> vector<vector<int>> {
            int Y = mat.size(), X = mat[0].size();
            vector<vector<int>> ret(Y, vector<int>(X));

            for (int y = 0; y < Y; ++y)
                for (int x = 0; x + 1 < X; ++x)
                    ret[y][x+1] = mat[y][x];

            for (int y = 0; y + 1 < Y; ++y)
                ret[y+1][0] = mat[y][X-1];

            ret[0][0] = mat[Y-1][X-1];
            return ret;
        };

        vector<vector<int>> ret = grid;
        while (k--) {
            ret = shift(grid);
            grid = ret;
        }
        return ret;
    }
};