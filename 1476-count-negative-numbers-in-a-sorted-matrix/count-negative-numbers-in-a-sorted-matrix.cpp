class Solution {
    int bs(vector<int>& row) {
        int s = -1, e = row.size();
        while (s + 1 < e) {
            int m = (s + e)/2;
            if (row[m] >= 0) s = m;
            else e = m;
        }
        return s;
    }
public:
    int countNegatives(vector<vector<int>>& grid) {
        int Y = grid.size();
        int X = grid[0].size();

        int cnt = 0;
        for (int y = 0; y < Y; ++y) {
            int x = bs(grid[y]);
            cout << x << endl;
            cnt += (X - x - 1);
        }

        return cnt;
    }
};