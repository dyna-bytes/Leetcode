#ifdef DBF
#define debug(x) cout << #x << " is " << x << endl;
#else
#define debug(x)
#endif
class Solution {
    class UnionFind {
        #define ROOT INT_MIN
        unordered_map<int, int> parent;
        unordered_map<int, int> rank;
    public:
        UnionFind(vector<int>& nums) {
            for (int n: nums)
                parent[n] = ROOT;
            for (int n: nums)
                rank[n] = 1;
        }
        void merge(int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v) return;
            rank[u] += rank[v];
            parent[v] = u;
        }
        int find(int u) {
            if (parent[u] == ROOT) return u;
            return parent[u] = find(parent[u]);
        }
        bool exist(int u) {
            return parent.count(u);
        }
        int returnMaxLength() {
            int ret = 0;
            for (auto [node, len]: rank) {
                ret = max(ret, len);
            }
            return ret;
        }
    };
public:
    int longestConsecutive(vector<int>& nums) {
        UnionFind uf(nums);
        for (int n: nums) {
            if (uf.exist(n - 1) && uf.find(n - 1) != uf.find(n)) {
                debug(n - 1);
                debug(n);
                debug(uf.find(n - 1));
                debug(uf.find(n));
                uf.merge(n - 1, n);
            }
        }

        return uf.returnMaxLength();
    }
};