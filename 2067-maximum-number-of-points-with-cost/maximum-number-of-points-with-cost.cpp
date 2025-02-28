class Solution {
public:
    int Y, X;
    vector<vector<long long>> memo;

    // memo[y+1][x] = points[y+1][x] + max(memo[y][0]-abs(x-0), ... , memo[y][n]-abs(x-n))
    // f(0 <= x < n) = max(memo[y][0]-abs(x-0), ..., memo[y][x-1] - 1, memo[y][x], memo[y][x+1] - 1, ...,  memo[y][n]-abs(x-n))
    // == max(f(0 <= l < x), memo[y][x], f(x <= x < n))

    void findMax(vector<vector<int>>& points) {
        for (int x = 0; x < X; x++)
            memo[0][x] = points[0][x];
            
        for (int y = 0; y < Y-1; y++) {
            vector<long long> leftMax(X), rightMax(X);
            leftMax[0] = memo[y][0];
            rightMax[X-1] = memo[y][X-1];

            for (int x = 1; x < X; x++) 
                leftMax[x] = max(leftMax[x-1] - 1, memo[y][x]);
            for (int x = X-2; x >= 0; x--)
                rightMax[x] = max(rightMax[x+1] - 1, memo[y][x]);
            for (int x = 0; x < X; x++) 
                memo[y+1][x] = points[y+1][x] + max(leftMax[x], rightMax[x]);
    
        }
    }

    long long maxPoints(vector<vector<int>>& points) {
        Y = points.size(), X = points[0].size();
        memo.resize(Y, vector<long long>(X, 0));
        
        findMax(points);

        long long maxScore = *max_element(memo[Y-1].begin(), memo[Y-1].end());
        return maxScore;
    }
};


/*
# top-down approach
```
long long findMaxInRow(int y, int x, vector<vector<int>>& points) {
        if (y == 0) return points[0][x];
        if (memo[y][x] != -1) return memo[y][x];

        long long maxScore = 0;
        for (int nx = 0; nx < X; nx++)
        maxScore = max(maxScore, 
            points[y][x] + findMaxInRow(y-1, nx, points) - abs(nx - x));
        
        return memo[y][x] = maxScore;
}
```

Get recursive expression from the above approach.
`memo[y+1][x] = points[y+1][x] + max(memo[y][0]-abs(x-0), ... , memo[y][n]-abs(x-n))`

# bottom-up approach
Using the recursvie expression, I can build a bottom-up approach solution.
```
void findMax(vector<vector<int>>& points) {
        for (int x = 0; x < X; x++)
            memo[0][x] = points[0][x];
            
        for (int y = 0; y < Y-1; y++) {
            for (int x = 0; x < X; x++) {
                for (int xx = 0; xx < X; xx++)
                    memo[y+1][x] = max(memo[y+1][x], 
                        points[y+1][x] + memo[y][xx] - abs(x - xx));
            }
        }
}
```

But its time complexity is O(Y * X * X), since to get
`max(for (w) { memo[y][x]-abs(x-w) })` is same with `for (x) { for (w) memo[y][x]-abs(x-w) }`.

The double loop comes from the bound relation between `x` and `w`.
To release this bound relation, the range of `for (w)` or `for (x)` should be 1.


We can define a new subproblem in a row that,
for `leftMax[x] = max(leftMax[x-1] - 1, memo[y][x])`
and `rightMax[x] = max(rightMax[x+1]-1, memo[y][x])`,
the recursive relation expresion is formed
```
max[x] = max(leftMax[x], rightMax[x]) = max(leftMax[x-1] - 1, memo[y][x], rightMax[x+1] + 1) 
= max(memo[y][0] - x, memo[y][1] - (x - 1), ... , memo[y][x], ... , memo[y][X-1] - (X - 1 - x))
```
*/