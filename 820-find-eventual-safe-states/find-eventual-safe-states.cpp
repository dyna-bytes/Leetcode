#define DBG
#ifdef DBG
#define debug(x)                                                               \
    std::cout << "[ " << __func__ << "](" << __LINE__ << ") " << #x << " is "  \
              << x << endl
#define debugVec(v)                                                            \
    do {                                                                       \
        std::cout << "[Debug] [";                                              \
        for (int i = 0; i < ((v.size()) - 1); i++)                             \
            std::cout << v[i] << "|";                                          \
        std::cout << v[((v.size()) - 1)] << "]\n";                             \
    } while (0)
#else
#define debug(x)
#define debugVec(v)
#endif
class Solution {
    unordered_set<int> safes;
    vector<int> visited;
    int dfs(int curr, vector<vector<int>>& adjs) {
        if (safes.find(curr) != safes.end())
            return true;

        if (visited[curr])
            return false;
        visited[curr] = true;

        for (int next : adjs[curr]) {
            if (!dfs(next, adjs))
                return false;
        }

        safes.insert(curr);
        return true;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> indegree(graph.size(), 0);
        vector<int> outdegree(graph.size(), 0);

        for (int from = 0; from < graph.size(); from++) {
            for (int to : graph[from]) {
                indegree[to]++;
                outdegree[from]++;
            }
        }

        for (int node = 0; node < graph.size(); node++)
            if (outdegree[node] == 0)
                safes.insert(node);

        visited.resize(graph.size(), false);
        vector<int> ret;
        for (int node = 0; node < graph.size(); node++) {
            if (dfs(node, graph))
                ret.push_back(node);
        }

        return ret;
    }
};