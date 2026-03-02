// #define DBG
#ifdef DBG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(c)
#endif
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> maxRight(n, 0);
        for (int y = 0; y < n; ++y) {
            for (int x = n-1; x >= 0; --x) {
                if (grid[y][x] == 1) {
                    maxRight[y] = x;
                    break;
                }
            }
        }
        
        debugVect(maxRight);

        int cnt = 0;
        for (int i = 0, j; i < n - 1; ++i) {
            if (maxRight[i] <= i) continue;

            for (j = i + 1; j < n; ++j)
                if (maxRight[j] <= i) break;

            if (j == n) return -1;

            for (int k = j-1; k >= i; --k) {
                swap(maxRight[k+1], maxRight[k]);
                cnt++;
            }
        }

        debugVect(maxRight);
        return cnt;
    }
};