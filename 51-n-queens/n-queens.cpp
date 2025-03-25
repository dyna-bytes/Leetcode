class Solution {
    int N;
    unordered_map<int, bool> visited_x;
    unordered_map<int, bool> visited_left_offset;
    unordered_map<int, bool> visited_right_offset;
    int get_left_offset(int y, int x) { return y - x; }
    int get_right_offset(int y, int x) { return y + x; }
public:
    vector<vector<string>> solveNQueens(int n) {
        N = n;
        vector<string> board;
        vector<vector<string>> ret;
        backtracking(0, board, ret);
        return ret;
    }

    void backtracking(int y, vector<string>& board, vector<vector<string>>& ret) {
        if (y == N) {
            ret.push_back(board);
            return;
        }

        string row;
        int loffset, roffset;
        for (int x = 0; x < N; x++) {
            if (visited_x[x]) continue;
            if (visited_left_offset[loffset = get_left_offset(y, x)]) continue;
            if (visited_right_offset[roffset = get_right_offset(y, x)]) continue;

            visited_x[x] = true;
            visited_left_offset[loffset] = true;
            visited_right_offset[roffset] = true;

            row = string(x, '.') + 'Q' + string(N-x-1, '.');
            board.push_back(row);
            backtracking(y+1, board, ret);

            board.pop_back();
            visited_x[x] = false;
            visited_left_offset[loffset] = false;
            visited_right_offset[roffset] = false;
        }
    }
};