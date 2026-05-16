class Solution {
    const int dy[4] = {0, 1, 0, -1}, dx[4] = {1, 0, -1, 0};
    int Y, X;
    vector<vector<int>> room;
    vector<vector<set<int>>> visited;
    bool inRange(int y, int x) {
        return 0 <= y && y < Y && 0 <= x && x < X;
    }
    int dfs(int y, int x, int dir) {
        int ret = visited[y][x].size() == 1;
        for (int d = dir; d < dir + 4; d++) {
            int ndir = d % 4;
            int ny = y + dy[ndir], nx = x + dx[ndir];
            if (!inRange(ny, nx)) continue;
            if (room[ny][nx]) continue;
            if (visited[ny][nx].count(ndir)) break;
            visited[ny][nx].insert(ndir);
            ret += dfs(ny, nx, ndir);
            break;
        }
        return ret;
    }
public:
    int numberOfCleanRooms(vector<vector<int>>& room) {
        this->room = room;
        Y = room.size(), X = room[0].size();
        visited.assign(Y, vector<set<int>>(X));

        visited[0][0] = {0};
        return dfs(0, 0, 0);
    }
};