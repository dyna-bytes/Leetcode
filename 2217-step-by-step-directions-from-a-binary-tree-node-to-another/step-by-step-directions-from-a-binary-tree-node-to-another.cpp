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
    bool dfs(TreeNode* curr, int val, string& path) {
        if (curr->val == val) return true;

        if (curr->left && dfs(curr->left, val, path)) {
            path.push_back('L');
            return true;
        } else if (curr->right && dfs(curr->right, val, path)) {
            path.push_back('R');
            return true;
        }

        return false;    
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        string S, D;
        dfs(root, startValue, S);
        dfs(root, destValue, D);

        // remove common prefix
        while (!S.empty() && !D.empty() && S.back() == D.back()) {
            S.pop_back(), D.pop_back();
        }

        return string(S.size(), 'U') + string(D.rbegin(), D.rend());
    }
};