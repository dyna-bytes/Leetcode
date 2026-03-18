class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int Y = grid.size(), X = grid[0].size();

        vector<vector<int>> pref(Y + 1, vector<int>(X + 1, 0));
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                pref[y + 1][x + 1] = pref[y + 1][x] + pref[y][x + 1]
                    - pref[y][x] + grid[y][x];
            }
        }

        int ret = 0;
        for (int y = 1; y <= Y; y++) {
            for (int x = 1; x <= X; x++) {
                if (pref[y][x] <= k)
                    ret++;
            }
        }
        return ret;
    }
};