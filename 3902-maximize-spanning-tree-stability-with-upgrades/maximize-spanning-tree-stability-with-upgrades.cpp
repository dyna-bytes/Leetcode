#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) {
        parent.resize(n + 1, -1);
    }
    int find(int u) {
        if (parent[u] < 0) return u;
        return parent[u] = find(parent[u]);
    }
    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;

        parent[u] += parent[v];
        parent[v] = u;
        return true;
    }
};

class Solution {
    int n;
    vector<vector<int>> edges;
    int k;

    bool check(int mid) {
        UnionFind uf(n);
        int edges_used = 0;
        int upgrades = 0;

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], s = edge[2], must = edge[3];
            if (must == 1) {
                if (s < mid) return false; 
                if (!uf.merge(u, v)) return false;
                
                edges_used++;
            }
        }

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], s = edge[2], must = edge[3];
            if (must == 0 && s >= mid) {
                if (uf.merge(u, v)) edges_used++;
                
            }
        }

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], s = edge[2], must = edge[3];
            if (must == 0 && s < mid && s * 2 >= mid) {
                if (uf.merge(u, v)) {
                    edges_used++;
                    upgrades++;
                }
            }
        }

        return edges_used == n - 1 && upgrades <= k;
    }
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        this->n = n;
        this->edges = edges;
        this->k = k;

        if (!check(0)) return -1;

        int max_s = 0;
        for (auto& edge: edges)
            max_s = max(max_s, edge[2]);

        int l = 1;
        int r = max_s * 2;
        int ans = -1;

        while (l <= r) {
            int mid = (l + r) / 2;

            if (check(mid)) {
                l = mid + 1;
                ans = mid;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};