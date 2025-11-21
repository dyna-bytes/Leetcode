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
    unordered_map<int, vector<TreeNode*>> dp;
    vector<TreeNode*> dfs(int n) {
        if (n == 1) {
            TreeNode* node = new TreeNode();
            return { node };
        }
        if (dp.count(n)) return dp[n];

        vector<TreeNode*> ret;
        for (int i = 1; i < n; i += 2) {
            auto lefts = dfs(i);
            auto rights = dfs(n - i - 1); 

            for (auto& left: lefts) {
                for (auto& right: rights) {
                    TreeNode* node = new TreeNode();
                    node->left = left;
                    node->right = right; 
                    ret.push_back(node);
                }
            }
        }
        return dp[n] = ret;
    }
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        return dfs(n);
    }
};