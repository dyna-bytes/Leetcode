#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Solution {
    int Y, X;
    int k;
    vector<vector<int>> grid;
    int getmindiff(int sy, int sx) {
        set<int> st;
        for (int y = sy; y < min(Y, sy + k); y++)
            for (int x = sx; x < min(X, sx + k); x++)
                st.insert(grid[y][x]);

        if (st.size() <= 1) return 0;
        
        int mindiff = INT_MAX;
        auto it = st.begin();
        for (++it; it != st.end(); it++) {
            int diff = abs(*it - *prev(it));
            mindiff = min(mindiff, diff);
        }
        return mindiff;
    }
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        Y = grid.size(), X = grid[0].size();
        this->grid = grid;
        this->k = k;

        vector<vector<int>> ret(Y - k + 1, vector<int>(X - k + 1, 0));
        for (int y = 0; y < Y - k + 1; y++) {
            for (int x = 0; x < X - k + 1; x++) 
                ret[y][x] = getmindiff(y, x);
        }
        return ret;
    }
};