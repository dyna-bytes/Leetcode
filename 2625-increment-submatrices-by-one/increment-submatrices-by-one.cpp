#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
    cout << endl; \
} while (0)

class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> psum(n+1, vector<int>(n+1, 0));
        for (auto& query: queries) {
            int y1 = query[0], x1 = query[1], y2 = query[2], x2 = query[3];
            y2++, x2++;
            psum[y1][x1]++;
            psum[y1][x2]--;
            psum[y2][x1]--;
            psum[y2][x2]++;
        }

        vector<vector<int>> ans(n, vector<int>(n, 0));
        for (int y = 0; y < n; y++) 
            for (int x = 0; x < n; x++)
                psum[y][x+1] += psum[y][x];

        for (int y = 0; y < n; y++) 
            for (int x = 0; x < n; x++)
                psum[y+1][x] += psum[y][x];

        for (int y = 0; y < n; y++)
            for (int x = 0; x < n; x++)
                ans[y][x] = psum[y][x];
        
        return ans;
    }
};