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
    unordered_map<TreeNode*, unordered_map<int, int>> dp;
public:
    int rob(TreeNode* root) {
        return theif(root, false);
    }

    int theif(TreeNode* curr, int robbed_prev) {
        if (!curr) return 0;

        if (dp[curr].count(robbed_prev))
            return dp[curr][robbed_prev];
        int& ret = dp[curr][robbed_prev];

        if (robbed_prev)
            ret = theif(curr->left, false) + theif(curr->right, false);
        else 
            ret = max(
                curr->val + theif(curr->left, true) + theif(curr->right, true),
                theif(curr->left, false) + theif(curr->right, false)
            );
        return ret;
    }
};