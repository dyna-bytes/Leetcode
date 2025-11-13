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

#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    unordered_map<TreeNode*, vector<TreeNode*>> adj;
    unordered_map<TreeNode*, bool> visited;

    void construct_graph(TreeNode *curr) {
        if (!curr) return;

        if (curr->left) {
            adj[curr].push_back(curr->left);
            adj[curr->left].push_back(curr);
            construct_graph(curr->left);
        }

        if (curr->right) {
            adj[curr].push_back(curr->right);
            adj[curr->right].push_back(curr);
            construct_graph(curr->right);
        }
    }

    pair<int, TreeNode*> find_farthest_from_root(TreeNode *curr) {
        if (!curr) return {0, nullptr};
        if (!curr->left && !curr->right) return {1, curr};

        int ret_len = -1;
        TreeNode* ret_ancs = nullptr;

        if (curr->left) {
            auto [left_len, left_ancs] = find_farthest_from_root(curr->left);
            if (ret_len < ++left_len) {
                ret_len = left_len;
                ret_ancs = left_ancs;
            }
        }

        if (curr->right) {
            auto [right_len, right_ancs] = find_farthest_from_root(curr->right);
            if (ret_len < ++right_len) {
                ret_len = right_len;
                ret_ancs = right_ancs;
            }
        }

        return {ret_len, ret_ancs};
    }

    int dfs(TreeNode *curr) {
        if (!curr) return 0;

        int ret = 0;
        for (auto next: adj[curr]) {
            if (visited[next]) continue;
            visited[next] = true;
            ret = max(ret, 1 + dfs(next));
        }
        return ret;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        construct_graph(root);
        auto [_, u] = find_farthest_from_root(root);
        debug(_);
        debug(u->val);
        
        visited[u] = true;
        return dfs(u);
    }
};