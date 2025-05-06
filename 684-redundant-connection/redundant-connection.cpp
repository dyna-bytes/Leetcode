// #define DBG
#ifdef DBG
#define debug(x)                                                               \
    std::cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is "   \
              << x << endl
#define debugVec(v)                                                            \
    do {                                                                       \
        std::cout << "[" << __func__ << "](" << __LINE__ << ") " << #v;        \
        std::cout << " [";                                                     \
        for (int i = 0; i < ((v.size()) - 1); i++)                             \
            std::cout << v[i] << "|";                                          \
        std::cout << v[((v.size()) - 1)] << "]\n";                             \
    } while (0)
#else
#define debug(x)
#define debugVec(v)
#endif
class Solution {
    class UnionFind {
        vector<int> root;

    public:
        UnionFind(int N) { root.resize(N, -1); }
        int find(int n) {
            int& ret = root[n];
            if (ret < 0)
                return n;
            return ret = find(ret);
        }
        bool merge(int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v)
                return false;

            if (root[u] >= root[v])
                swap(u, v);

            root[u] += root[v];
            root[v] = u;
            return true;
        }
    };

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> ret;
        int N = edges.size();
        UnionFind dsu(N + 1);
        vector<vector<int>> candidates;

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (!dsu.merge(u, v)) 
                candidates.push_back(edge);
        }

        int M = candidates.size();
        for (int i = N - 1; i >= 0; i--) {
            auto& edge = edges[i];
            for (int j = M - 1; j >= 0; j--) {
                auto& candi = candidates[j];
                if (edge == candi)
                    return candi;
            }
        }

        return ret;
    }
};