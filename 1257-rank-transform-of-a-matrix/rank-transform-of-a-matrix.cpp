#define debug(x) cout << #x << " is " << x << endl;
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
    typedef pair<int, int> pii;
    typedef tuple<int, pii> tup;
    int Y, X;
    int mapping(const pii& pos) {
        auto [y, x] = pos;
        return y * X + x;
    }
    pii unmapping(int k) {
        return { k / X, k % X };
    }
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        Y = matrix.size(), X = matrix[0].size();
        map<int, vector<pii>> vals;
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                vals[matrix[y][x]].push_back({ y, x });
        
        vector<vector<int>> rank(Y, vector<int>(X, 0));
        vector<int> row_max(Y, 0);
        vector<int> col_max(X, 0);
        UnionFind uf(Y*X + 1);

        for (auto& [val, positions]: vals) {
            // 1. 행 또는 열이 같은 노드를 찾아 merge
            unordered_map<int, vector<int>> rows, cols;
            for (auto& pos: positions) {
                auto [y, x] = pos;
                rows[y].push_back(x);
                cols[x].push_back(y);
            }

            for (auto& [y, xlist] : rows) {
                for (int i = 0; i < xlist.size() - 1; i++) {
                    uf.merge(mapping({y, xlist[i]}), mapping({y, xlist[i+1]}));
                }
            }

            for (auto& [x, ylist] : cols) {
                for (int i = 0; i < ylist.size() - 1; i++) {
                    uf.merge(mapping({ylist[i], x}), mapping({ylist[i+1], x}));
                }
            }
            
            // DSU root 가 같은 노드끼리 grouping (역 DSU)
            unordered_map<int, vector<pii>> groups;
            for (auto& pos: positions) {
                auto [y, x] = pos;
                int root = uf.find(mapping({y, x}));
                groups[root].push_back(pos);
            }

            // 동일한 group 전체의 max_rank 값을 계산. 일괄 rank 처리
            for (auto& [root, group_positions]: groups) {
                int max_rank = 0;

                for (auto& pos: group_positions) {
                    auto [y, x] = pos;
                    max_rank = max({max_rank, row_max[y], col_max[x]});
                }

                for (auto& pos: group_positions) {
                    auto [y, x] = pos;
                    rank[y][x] = max_rank + 1;
                    row_max[y] = max(row_max[y], max_rank + 1);
                    col_max[x] = max(col_max[x], max_rank + 1);
                }
            }
        }
        return rank;
    }
};