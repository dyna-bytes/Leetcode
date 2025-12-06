

bool inRange(int y, int x, int Y, int X) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

typedef struct {
    int y;
    int x;
} point;

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};
#define MAXSIZE ((300 * 300) * 4 + 1)
void bfs(int sy, int sx, int Y, int X, char** grid, int** visited) {
    point q[MAXSIZE];
    memset(q, 0, sizeof(q));
    int eq = 0, dq = 0;

    point p = {sy, sx};
    q[eq++] = p;
    visited[sy][sx] = true;

    while (dq < eq) {
        point curr = q[dq++];
        int y = curr.y, x = curr.x;

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];

            if (!inRange(ny, nx, Y, X)) continue;
            if (grid[ny][nx] == '0') continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = true;
            point np = {ny, nx};
            q[eq++] = np;
        }
    }
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int Y = gridSize;
    int X = gridColSize[0];

    int** visited = calloc(Y, sizeof(int *));
    for (int y = 0; y < Y; y++)
        visited[y] = calloc(X, sizeof(int));

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            visited[y][x] = false;

    int cnt = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            printf("%d ", visited[y][x]);
            if (!visited[y][x] && grid[y][x] == '1') {
                bfs(y, x, Y, X, grid, visited);
                cnt++;
            }
        }
        printf("\n");
    }

    return cnt;
}