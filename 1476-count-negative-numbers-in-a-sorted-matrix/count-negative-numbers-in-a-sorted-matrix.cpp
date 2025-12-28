class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int Y = grid.size();
        int X = grid[0].size();

        int cnt = 0;
        for (int y = 0; y < Y; ++y)
            for (int x = 0; x < X; ++x)   
                if (grid[y][x] < 0) cnt++;
        return cnt;
    }
};