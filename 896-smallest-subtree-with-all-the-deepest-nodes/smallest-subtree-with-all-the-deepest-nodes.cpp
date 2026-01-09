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
    int max_lv = -1;
    TreeNode* lca;
    int dfs(TreeNode* curr, int lv) {
        if (!curr) return lv;

        int left_lv = dfs(curr->left, lv + 1);
        int right_lv = dfs(curr->right, lv + 1);

        if (max_lv <= left_lv && max_lv <= right_lv)
            lca = curr;
        max_lv = max({max_lv, left_lv, right_lv});
        return max(left_lv, right_lv);
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        dfs(root, 0);
        return lca;
    }
};