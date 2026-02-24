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
    int ret;
    int bintodec(int bin) {
        int dec = 0;
        int i = 0;
        while (bin) {
            dec += ((bin & 1) << i);
            bin >>= 1;
            i++;
        }
        return dec;
    }
    void dfs(TreeNode* curr, int bin) {
        if (!curr)
            return;

        if (curr->left)
            dfs(curr->left, bin << 1 | (curr->val));
        if (curr->right)
            dfs(curr->right, bin << 1 | (curr->val));
        if (curr->left == nullptr && curr->right == nullptr) 
            ret += bintodec(bin << 1 | (curr->val));
    }
public:
    int sumRootToLeaf(TreeNode* root) {
        ret = 0;
        dfs(root, 0);
        return ret;
    }
};