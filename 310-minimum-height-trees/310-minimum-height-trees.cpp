class Solution {
    
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n < 2){
            vector<int> centroids(n);
            for(int i = 0; i < n; i++)
                centroids[i] = i;
            return centroids;
        }
        
        vector<vector<int>> adj(n);
        for(vector<int> edge : edges){
            int from = edge[0], to = edge[1];
            adj[from].push_back(to);
            adj[to].push_back(from);
        }
        
        vector<int> leaves;
        for(int i = 0; i < n; i++)
            if(adj[i].size() == 1) // 인접리스트에서 말단 노드를 찾음
                leaves.push_back(i);
        
        int remaining = n;
        while(remaining > 2){
            remaining -= leaves.size();
            vector<int> newLeaves;
            
            for(int leaf : leaves){
                int next = adj[leaf][0];
                // delete edge from next to leaf
                for(int i = 0; i < adj[next].size(); i++)
                    if(adj[next][i] == leaf) {
                        adj[next].erase(adj[next].begin() + i);
                        break;
                    }
                
                // find new leaves
                if(adj[next].size() == 1)
                    newLeaves.push_back(next);
            }
            leaves = newLeaves;
        }
        
        return leaves;
    }
};