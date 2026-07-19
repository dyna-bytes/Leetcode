class Solution {
    vector<vector<char>> board;
    vector<vector<int>> rows;
    vector<vector<int>> cols;
    vector<vector<int>> groups;
    int solve(int idx) {
        if (idx >= 81) return true;
        int y = idx / 9;
        int x = idx % 9;
        int grp = 3 * (y / 3) + (x / 3);

        int val = (board[y][x] == '.') ? 0 : (board[y][x] - '0');
        if (val) {
            rows[y][val] = cols[x][val] = groups[grp][val] = true;
            return solve(idx + 1);
        }

        for (int n = 1; n <= 9; ++n) {
            if (rows[y][n] || cols[x][n] || groups[grp][n]) continue;
            rows[y][n] = cols[x][n] = groups[grp][n] = true;
            board[y][x] = n + '0';
            if (solve(idx + 1)) return true;
            rows[y][n] = cols[x][n] = groups[grp][n] = false;
            board[y][x] = '.';
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        this->board = board;
        rows.assign(10, vector<int>(10, 0));
        cols.assign(10, vector<int>(10, 0));
        groups.assign(10, vector<int>(10, 0));
        for (int y = 0; y < 9; ++y)
            for (int x = 0; x < 9; ++x) {
                int grp = 3 * (y / 3) + (x / 3);
                int val = (board[y][x] == '.') ? 0 : (board[y][x] - '0');
                if (val == 0) continue;
                rows[y][val] = cols[x][val] = groups[grp][val] = true;
            }
        solve(0);
        board = this->board;
    }
};