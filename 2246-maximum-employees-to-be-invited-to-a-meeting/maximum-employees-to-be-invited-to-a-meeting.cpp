// #define DBG
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
    vector<pair<int, int>> two_cycles;
    vector<vector<int>> rev_adj;
    vector<int> dp;
    int cycle_dfs(int curr, int curr_depth, const int runID,
                  const vector<int>& adj, vector<int>& depth) {
        if (visited[curr] == runID)
            return curr_depth - depth[curr];

        if (visited[curr])
            return 0;

        visited[curr] = runID;
        depth[curr] = curr_depth;
        return cycle_dfs(adj[curr], curr_depth + 1, runID, adj, depth);
    }

    int acycle_dp(int curr, int counter_start, vector<vector<int>>& rev_adj) {
        int& ret = dp[curr];
        if (ret != -1)
            return ret;

        int max_len = 0;
        for (int next : rev_adj[curr]) {
            if (next == counter_start)
                continue;
            max_len = max(max_len, 1 + acycle_dp(next, counter_start, rev_adj));
        }
        return ret = max_len;
    }

public:
    int maximumInvitations(vector<int>& favorite) {
        int N = favorite.size();
        visited.resize(N, 0);
        depth.resize(N, 0);
        rev_adj.resize(N);
        dp.resize(N, -1);
        for (int from = 0; from < N; from++) {
            int to = favorite[from];
            if (from < to && favorite[to] == from)
                two_cycles.push_back({from, to});

            rev_adj[to].push_back(from);
        }

        int max_cycle_len = 0;
        for (int n = 0; n < N; n++) {
            max_cycle_len =
                max(max_cycle_len, cycle_dfs(n, 1, n + 1, favorite, depth));
        }

        int sum_acycle_Len = 0;
        for (auto& [from, to] : two_cycles) {
            int u = 1 + acycle_dp(from, to, rev_adj);
            int v = 1 + acycle_dp(to, from, rev_adj);
            sum_acycle_Len += (u + v);
        }

        return max(max_cycle_len, sum_acycle_Len);
    }
};