#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef long long ll;
    int Y, X;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
    vector<vector<int>> grid;
    vector<vector<map<int, ll>>> dp;
    int f(int y, int x, int diff) {
        diff += (grid[y][x] ? 1 : -1);

        if (y == Y-1 && x == X-1) {
            return diff == 0;
        } 

        if (dp[y][x].count(diff)) return dp[y][x][diff];

        ll ret = 0;

        if (inRange(y+1, x))
            ret += f(y+1, x, diff);
        if (inRange(y, x+1))
            ret += f(y, x+1, diff);
        return dp[y][x][diff] = ret;
    }
public:
    bool isThereAPath(vector<vector<int>>& grid) {
        this->grid = grid;
        Y = grid.size(), X = grid[0].size();
        dp.assign(Y+1, vector<map<int, ll>>(X+1));
        return f(0, 0, 0);
    }
};