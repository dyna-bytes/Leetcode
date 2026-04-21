class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) {
        parent.assign(n + 1, -1);
    }

    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;

        parent[u] += parent[v];
        parent[v] = u;
    }
};

class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        UnionFind uf(n);
        for (vector<int>& swaps: allowedSwaps) {
            int u = swaps[0], v = swaps[1];
            uf.merge(u, v);
        }

        unordered_map<int, unordered_set<int>> groups;
        for (int i = 0; i < n; i++) {
            groups[uf.find(i)].insert(i);
        }

        int ret = 0;
        for (auto& [_, group]: groups) {
            unordered_multiset<int> src;
            for (int idx: group) 
                src.insert(source[idx]);
            
            for (int idx: group) {
                auto it = src.find(target[idx]);
                if (it == src.end()) ret++;
                else src.erase(it);
            }
        }

        return ret;
    }
};