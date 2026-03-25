class Solution {
    typedef long long ll;
    vector<vector<int>> rotate(const vector<vector<int>>& grid) {
        int Y = grid.size(), X = grid[0].size();
        vector<vector<int>> ret(X, vector<int>(Y));

        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                ret[x][Y - 1 - y] = grid[y][x];
        return ret;
    }
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        ll total = 0;

        for (vector<int>& row: grid)
            for (int val: row)
                total += val;

        auto check = [](const vector<vector<int>>& grid, ll total) {
            int Y = grid.size(), X = grid[0].size();
            ll sum = 0;
            unordered_map<ll, bool> mp;

            // count row from top
            for (int y = 0; y < Y; y++) {
                ll sum_row = 0;
                for (int x = 0; x < X; x++) {
                    mp[grid[y][x]] = true;
                    sum_row += grid[y][x];
                }

                sum += sum_row;
                if (sum * 2 == total) return true;
                else if (sum * 2 > total) {
                    ll other = total - sum;
                    ll diff = abs(sum - other);
                    bool is_line = (y == 0) || (X == 1);

                    if (is_line) { 
                        if (grid[y][0] == diff) return true;
                        if (grid[y][X-1] == diff) return true;
                        if (grid[0][0] == diff) return true;   // Top-Left
                        if (grid[0][X-1] == diff) return true; // Top-Right
                    } else if (mp[diff]) return true;
                }
            }

            return false;
        };

         for (int i = 0; i < 4; ++i) {
            if (check(grid, total)) return true;
            if (i < 3) grid = rotate(grid); 
        }

        return false;
    }
};