class Solution {
    typedef pair<int, int> pii;
    int Y, X;
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    } 
public:
    void setZeroes(vector<vector<int>>& matrix) {
        Y = matrix.size(), X = matrix[0].size();
        queue<pii> q;
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                if (matrix[y][x] == 0) q.push({y, x});

        while (q.size()) {
            auto [y, x] = q.front(); 
            q.pop();

            for (int d = 0; d < 4; d++) {
                for (int dist = 0; dist < max(Y, X); dist++) {
                    int ny = y + dist * dy[d], nx = x + dist * dx[d];
                    if (!inRange(ny, nx)) continue;
                    matrix[ny][nx] = 0;
                }
            }
        }
    }
};