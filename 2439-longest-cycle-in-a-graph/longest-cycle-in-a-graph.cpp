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
    vector<int> visited;
    vector<int> depth;
    int bfs(int start, int level, vector<int>& edges) {
        int curr = start;
        int curr_depth = 1;

        while (true) {
            if (visited[curr]) {
                if (visited[curr] == level)
                    return curr_depth - depth[curr];
                return -1;
            }

            visited[curr] = level;
            depth[curr] = curr_depth++;

            curr = edges[curr];
            if (curr == -1) return -1;
        }
    }
public:
    int longestCycle(vector<int>& edges) {
        int N = edges.size();
        visited.resize(N, 0);
        depth.resize(N, 0);
        int max_cycle = -1;
        int level = 1;
        for (int n = 0; n < N; n++, level++) {
            max_cycle = max(max_cycle, 
                bfs(n, level, edges));
        }
        return max_cycle;
    }
};