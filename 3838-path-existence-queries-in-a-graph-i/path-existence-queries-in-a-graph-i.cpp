#define debug(x) cout << #x << " is " << x << endl;

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) {
        parent.assign(n, -1);
    }
    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (parent[v] < parent[u]) swap(u, v);
        parent[v] += parent[u];
        parent[u] = v;
    }
};

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        UnionFind uf(n);

        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i + 1] - nums[i] <= maxDiff)
                uf.merge(i, i + 1);
        }

        vector<bool> ret(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            int u = queries[i][0];
            int v = queries[i][1];
            ret[i] = (uf.find(u) == uf.find(v));
        }
        return ret;
    }
};