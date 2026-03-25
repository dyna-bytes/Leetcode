class Solution {
    typedef long long ll;
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int Y = grid.size(), X = grid[0].size();
        vector<ll> row_sums(Y, 0);
        vector<ll> col_sums(X, 0);
        vector<ll> pref_row(Y + 1, 0);
        vector<ll> pref_col(X + 1, 0);

        for (int y = 0; y < Y; y++) {
            ll sum = 0;
            for (int x = 0; x < X; x++)
                sum += grid[y][x];

            row_sums[y] = sum;
        }

        for (int i = 0; i < Y; i++)
            pref_row[i + 1] = pref_row[i] + row_sums[i];

        for (int x = 0; x < X; x++) {
            ll sum = 0;
            for (int y = 0; y < Y; y++)
                sum += grid[y][x];
            
            col_sums[x] = sum;
        }
            
        for (int i = 0; i < X; i++)
            pref_col[i + 1] = pref_col[i] + col_sums[i];

        int ans = 0;
        for (int i = 1; i < Y; i++)
            if (pref_row[i] == pref_row[Y] - pref_row[i])
                ans++;

        for (int i = 1; i < X; i++)
            if (pref_col[i] == pref_col[X] - pref_col[i])
                ans++;

        return ans;
    }
};