class Solution {
class UnionFind {
    vector<int> parent;
    vector<int> cache;
public:
    UnionFind(int n) {
        parent.resize(n+1, -1);
        cache.resize(n+1);
    }

    int find(int n) {
        int& ret = parent[n];
        if (ret < 0) return n;
        return ret = find(ret);
    }
    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        parent[v] = u;
        return true;
    }
    void keep() {
        cache = parent;
    }
    void restore() {
        parent = cache;
    }
};
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        UnionFind uf(n);
        vector<bool> results(requests.size());

        auto check = [&](UnionFind& uf) {
            for (auto& restriction: restrictions) {
                int a = restriction[0], b = restriction[1];
                a = uf.find(a);
                b = uf.find(b);

                if (a == b) {
                    uf.restore();
                    return false;
                }
            }
            return true;
        };

        for (int i = 0; i < requests.size(); i++) {
            auto& request = requests[i];
            int u = request[0], v = request[1];
            u = uf.find(u);
            v = uf.find(v);
            uf.keep();

            if (!uf.merge(u, v)) {
                results[i] = true;
                continue;
            }

            results[i] = check(uf);
        }

        return results;
    }
};