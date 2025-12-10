#define min(a, b) ((a) < (b) ? (a) : (b))
const int dy[2] = {0, 1}, dx[2] = {1, 0};
bool inRange(int y, int x, int Y, int X) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

int f(int y, int x, int** grid, int Y, int X, int** dp) {
    if (y == Y-1 && x == X-1) return grid[y][x];
    if (dp[y][x]) return dp[y][x];

    int ret = INT_MAX;
    for (int d = 0; d < 2; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx, Y, X)) continue;

        ret = min(ret, f(ny, nx, grid, Y, X, dp));
    }

    ret += grid[y][x];
    return dp[y][x] = ret;
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int Y = gridSize, X = *gridColSize;
    int** dp = calloc(Y, sizeof(int*));
    dp[0] = calloc(Y * X, sizeof(int));
    for (int y = 1; y < Y; y++)
        dp[y] = dp[y-1] + X;

    int ret = f(0, 0, grid, Y, X, dp);
    free(dp[0]);
    free(dp);
    return ret;
}