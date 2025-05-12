// #define DBG
#ifdef DBG
#define debug(x) std::cout << "[ " << __func__ << "](" << __LINE__ << ") " \
    << #x << " is " << x << endl
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
#else
#define debug(x)
#define debugVec(v)
#endif
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> edges(n+1);
        vector<int> indegree(n+1, 0);
        vector<int> visited(n+1, 0);
        for (auto& rel: relations) {
            int from = rel[0], to = rel[1];
            edges[from].push_back(to);
            indegree[to]++;
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indegree[i]) continue;
            q.push(i);
            visited[i] = time[i-1];
        }

        int res = 0;
        while (!q.empty()) {
            int qsize = q.size();
            for (int i = 0; i < qsize; i++) {
                int curr = q.front(); q.pop();
                res = max(res, visited[curr]);

                for (int next: edges[curr]) {
                    if (visited[next] >= visited[curr] + time[next - 1])
                        continue;
                    visited[next] = visited[curr] + time[next - 1];
                    q.push(next);
                }
            }
        }
        return res;
    }  
};