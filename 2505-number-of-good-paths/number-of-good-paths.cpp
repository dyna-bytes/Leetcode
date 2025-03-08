class Solution {
public:
    vector<int> parent;
    
    int find(int n) {
        if (parent[n] < 0) return n;
        parent[n] = find(parent[n]);
        return parent[n];
    }
    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return true;

        parent[u] += parent[v];
        parent[v] = u;
        return false;
    }

    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int N = vals.size();

        parent.resize(N, -1);
        vector<vector<int>> adj(N);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (vals[u] < vals[v]) swap(u, v);
            adj[u].push_back(v);
        }

        map<int, vector<int>> sameNodes;
        for (int i = 0; i < N; i++)
            sameNodes[vals[i]].push_back(i);

        int goodPaths = 0;
        for (auto& [val, nodes]: sameNodes) {
            for (int node: nodes) 
                for (int nbr: adj[node]) 
                    merge(node, nbr);
                
            unordered_map<int, int> disjoint_set;
            
            for (int node: nodes)
                disjoint_set[find(node)]++;

            for (auto& [_, size]: disjoint_set)
                goodPaths += (size * (size + 1))/2;
        }
        return goodPaths;
    }
};