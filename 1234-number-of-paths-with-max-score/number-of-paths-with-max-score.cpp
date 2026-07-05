class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
    const int dy[4] = {1, 0, 1}, dx[4] = {0, 1, 1}; // down, right, down-right
    const int mod = 1e9 + 7;
    int N;
    vector<string> board;
    vector<vector<int>> dp, dp2;

    bool inRange(int y, int x) {
        return 0 <= y && y < N && 0 <= x && x < N;
    }

    int f(int y, int x) {
        if (y == N-1 && x == N-1) return 0;

        int& ret = dp[y][x];
        if (ret != -2) return ret;
        ret = -1;

        for (int d = 0; d < 3; ++d) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == 'X') continue;

            ret = max(ret, f(ny, nx));
        }

        if (ret == -1) return ret;
        ret += (board[y][x] == 'E' ? 0 : (board[y][x] - '0'));
        return ret;
    }

    int g(int y, int x) {
        if (y == N-1 && x == N-1) return 1;

        int& ret = dp2[y][x];
        if (ret != -1) return ret;

        ret = 0;
        int score = f(y, x) - (board[y][x] == 'E' ? 0 : (board[y][x] - '0'));
        for (int d = 0; d < 3; ++d) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (board[ny][nx] == 'X') continue;

            int next_score = f(ny, nx);
            if (score == next_score) {
                ret += g(ny, nx);
                ret %= mod;
            }
        }
        return ret;
    }
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        this->board = board;
        this->N = board.size();
        dp.assign(N, vector<int>(N, -2));
        dp2.assign(N, vector<int>(N, -1));
    
        int ret = f(0, 0);
        if (ret == -1) return {0, 0};

        return {ret, g(0, 0)};
    }
};