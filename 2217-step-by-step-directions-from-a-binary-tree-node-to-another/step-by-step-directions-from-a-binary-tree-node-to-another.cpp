/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    #define MAX_N 100005
    #define MAX_K 17
    int depth[MAX_N];
    int parent[MAX_N][MAX_K]; // parent[node][k] : 2^k jumps from node
    unordered_map<int, TreeNode*> mp;

    int dfs_downward(TreeNode* curr) {
        mp[curr->val] = curr;
        int nodes = 1;

        if (curr->left) {
            parent[curr->left->val][0] = curr->val;
            depth[curr->left->val] = depth[curr->val] + 1;
            nodes += dfs_downward(curr->left);
        }

        if (curr->right) {
            parent[curr->right->val][0] = curr->val;
            depth[curr->right->val] = depth[curr->val] + 1;
            nodes += dfs_downward(curr->right);
        }

        return nodes;
    }

    void construct(int N) {
        for (int k = 0; k < MAX_K-1; k++)
            for (int x = 1; x <= N; x++)
                if (parent[x][k] != -1)
                    parent[x][k+1] = parent[parent[x][k]][k];
    }

    // depth[u] >= depth[v]
    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) return getLCA(v, u);

        int diff = depth[u] - depth[v];
        cout << "diff: " << diff << endl;

        for (int k = MAX_K-1; k >= 0; k--) {
            if ((1 << k) & diff){
                cout << "k: " << k << " u: " << u << endl;
                u = parent[u][k];
            }
        }

        if (u == v) return u;

        for (int k = MAX_K-1; k >= 0; k--) {
            if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }

        return parent[u][0];
    }

    string dfs_upward(int curr, int lca) {
        if (curr == lca) return "";

        TreeNode* currNode = mp[curr];
        TreeNode* parentNode = mp[parent[curr][0]];

        if (parentNode->left == currNode) 
            return dfs_upward(parent[curr][0], lca) + "L";
        
        return dfs_upward(parent[curr][0], lca) + "R";
    }

    string getDir(int lca, int startValue, int destValue) {
        int diff = depth[startValue] - depth[lca];
        string ret;
        for (int i = 0; i < diff; i++) ret += "U";

        ret += dfs_upward(destValue, lca);
        return ret;
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        #include <cstring>
        memset(parent, -1, sizeof(parent));
        memset(depth, -1, sizeof(depth));

        depth[root->val] = 0;
        int N = dfs_downward(root);
        construct(N);

        int lca = getLCA(startValue, destValue);
        cout << "LCA: " << lca << endl;
        return getDir(lca, startValue, destValue);
    }
};