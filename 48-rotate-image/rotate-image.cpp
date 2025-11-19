#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#define debugVect2d(vv) do { \
    cout << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)

class Solution {
public:
    void rotate(vector<vector<int>>& mat) {
        int n = mat.size();

        for (int s = 0; s < n/2; s++) {
            vector<int> buf = mat[s];
            // debugVect2d(mat);

            for (int c = n-1-s; c >= s; c--) 
                mat[s][c] = mat[n-1-c][s];
            // debugVect2d(mat);

            for (int r = s; r < n-s; r++) 
                mat[r][s] = mat[n-1-s][r];
            // debugVect2d(mat);

            for (int c = s; c < n-s; c++)
                mat[n-1-s][c] = mat[n-1-c][n-1-s];
            // debugVect2d(mat);
            
            for (int r = s; r < n-s; r++)
                mat[r][n-1-s] = buf[r];
            // debugVect2d(mat);
        }
        // debugVect2d(mat);
    }
};

/*
 * 00 01 02
 * 10 11 12
 * 20 21 22

 * 20 10 00
 * 21 11 01
 * 22 12 02
*/