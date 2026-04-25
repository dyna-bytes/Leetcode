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
    typedef long long ll;
    vector<ll> A;
    int n;
    int LOG;
    vector<vector<ll>> up; // up[i][k]: 정점 i 에서 2^k 번 이동한 후의 정점

    bool check(ll x, int k) {
        vector<int> nxt(2*n + 1, 2*n); // 정점 i에서 거리가 x이상인 다음 정점

        for (int i = 0, j = 0; i < 2*n; i++) {
            for (; j < 2*n && A[j] - A[i] < x; j++)
            ;
            nxt[i] = j;
        }

        // 2^0 = 1번 점프 = nxt
        for (int i = 0; i < 2*n; i++)
            up[i][0] = nxt[i];

        for (int step = 1; step < LOG; step++) 
            for (int i = 0; i < 2*n; i++)
                up[i][step] = up[ up[i][step-1] ][step-1];
        
        for (int i = 0; i < n; i++) {
            int curr = i;
            for (int step = 0; step < LOG; step++) {
                if ((k >> step) & 1) {
                    curr = up[curr][step];
                    if (curr >= 2*n) break;
                }
            }

            if (curr <= i + n) return true;
        }
        return false;
    }
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        n = points.size();
        LOG = log2(k) + 2;
        up.assign(2*n + 1, vector<ll>(LOG, 2*n));

        auto getDist = [&](int x, int y) {
            if (y == 0) return 1LL*x;
            else if (x == side) return 1LL*side + y;
            else if (y == side) return 3LL*side - x;
            else if (x == 0) return 4LL*side - y;
            return 0LL;
        };

        vector<ll> arr(n);
        for (int i = 0; i < points.size(); i++) {
            int x = points[i][0], y = points[i][1];
            arr[i] = getDist(x, y);
        }

        sort(arr.begin(), arr.end());
        A.assign(2*n + 1, 0);
        for (int i = 0; i < n; i++) {
            A[i] = arr[i];
            A[i + n] = arr[i] + 4LL*side;
        }
        A[2*n] = 3e18;

        ll lo = 0, hi = 4LL*side + 1;
        while (lo + 1 < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (check(mid, k)) lo = mid;
            else hi = mid;
        }
        return lo;
    }
};