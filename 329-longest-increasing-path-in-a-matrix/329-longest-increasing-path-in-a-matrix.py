class Solution:
    Y = 0
    X = 0
    dy = [-1, 1, 0, 0]
    dx = [0, 0, -1, 1]

    def inRange(self, y: int, x: int):
        return y >= 0 and y < self.Y and x >= 0 and x < self.X

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        self.Y = len(matrix)
        self.X = len(matrix[0])
        dp = [[-1 for x in range(self.X)] for y in range(self.Y)]

        def dfs(y: int, x: int):
            if dp[y][x] != -1: return dp[y][x]

            curr = matrix[y][x]
            dp[y][x] = 0

            for dir in range(4):
                ny = y + self.dy[dir]
                nx = x + self.dx[dir]

                if not self.inRange(ny, nx): continue
                if matrix[ny][nx] <= curr: continue
                dp[y][x] = max(dp[y][x], dfs(ny, nx))

            dp[y][x] += 1
            return dp[y][x]

        ans = 0
        for y in range(self.Y):
            for x in range(self.X):
                ans = max(ans, dfs(y, x))

        return ans