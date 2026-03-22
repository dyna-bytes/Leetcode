#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#define debugVect2D(vv) do { \
    cout << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
    cout << endl; \
} while (0)

class Solution {
    vector<double> matmul(const vector<vector<double>>& rot, const vector<double>& vec) {
        int Y = rot.size();
        int X = rot[0].size();
        assert(X == vec.size());

        vector<double> ret(Y, 0);
        for (int y = 0; y < Y; y++) 
            for (int x = 0; x < X; x++)
                ret[y] += (rot[y][x] * vec[x]);
        return ret;
    }
    vector<vector<int>> rotate(vector<vector<int>>& mat) {
        int N = mat.size();
        vector<vector<int>> ret(N, vector<int>(N));

        double k = ((double)N - 1) / 2;
        vector<vector<double>> rot = {{0, -1}, {1, 0}};

        for (double y = 0; y < N; y++) 
            for (double x = 0; x < N; x++) {
                auto res = matmul(rot, vector<double>{ y - k, x - k });
                int ry = res[0] + k, rx = res[1] + k;
                ret[ry][rx] = mat[y][x];
            }
        return ret;
    }
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        for (int d = 0; d < 4; d++) {
            if (mat == target) return true;
            mat = rotate(mat);
        }
        return false;
    }
};