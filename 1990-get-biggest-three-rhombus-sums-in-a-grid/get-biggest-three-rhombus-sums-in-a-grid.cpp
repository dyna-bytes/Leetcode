#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;

class Solution {
                    // RD, LD, LU, RU
    const int dy[4] = {1, 1, -1, -1};
    const int dx[4] = {1, -1, -1, 1}; 

    int Y, X;
    vector<vector<int>> grid;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    int rhombus_sum(int y, int x, int l) {
        if (l == 1) return grid[y][x];

        int ret = 0;
        int ny, nx;
        l--;
        for (int d = 0; d < 4; d++) {
            for (int k = 0; k < l; k++) {
                ny = y + k*dy[d], nx = x + k*dx[d];
                if (!inRange(ny, nx)) return -1;

                ret += grid[ny][nx];
            }

            y = y + l*dy[d], x = x + l*dx[d];
            if (!inRange(y, x)) return -1;
        }
        return ret;
    }
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        Y = grid.size(), X = grid[0].size();
        this->grid = grid;

        set<int> st;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                for (int l = 1; l <= min(Y, X); l++) {
                    int sum = rhombus_sum(y, x, l);
                    if (sum == -1) break;

                    st.insert(sum);
                }
            }
        }

        vector<int> ret;
        while (st.size() && ret.size() < 3) {
            ret.push_back(*prev(st.end()));
            st.erase(prev(st.end()));
        }
        return ret;
    }
};