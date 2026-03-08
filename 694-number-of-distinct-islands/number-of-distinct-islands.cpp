#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
    typedef pair<int, int> pii;

    int Y, X;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }

    vector<vector<int>> grid;
    vector<vector<int>> visited;
    set<string> paths;
    map<int, char> dir_map;

    char itoc(int x) { return x + '0'; }

    void dfs(pii curr, string& path, int dir) {
        auto [y, x] = curr;

        path += dir_map[dir];
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            if (!grid[ny][nx]) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = true;
            dfs({ny, nx}, path, d); 
        }
        path += dir_map[-1];
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        Y = grid.size(), X = grid[0].size();
        this->grid = (const vector<vector<int>>&) grid;

        visited.resize(Y, vector<int>(X, 0));
        dir_map = {
            {0, 'U'},
            {1, 'D'},
            {2, 'L'},
            {3, 'R'},
            {-1, '0'}
        };
        
        for (int y = 0; y < Y; ++y) {
            for (int x = 0; x < X; ++x) {
                if (grid[y][x] && !visited[y][x]) {
                    visited[y][x] = true;
                    string path;
                    dfs({y, x}, path, -1);
                    // debug(path);
                    paths.insert(path);
                }
            }
        }

        return paths.size();
    }
};