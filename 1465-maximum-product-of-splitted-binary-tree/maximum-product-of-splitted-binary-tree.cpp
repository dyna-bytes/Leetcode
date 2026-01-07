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
    typedef long long ll;
    const ll mod = 1e9 + 7;
    ll total_sum = 0;
    ll max_product = 0;
    unordered_map<TreeNode *, ll> dp;

    ll accum(TreeNode *root) {
        if (!root) return 0;
        if (dp.count(root)) return dp[root];

        ll ret = root->val;
        ret += accum(root->left);
        ret += accum(root->right);

        return dp[root] = ret;
    }

    void dfs(TreeNode* root) {
        if (!root) return;

        ll subtree_sum = accum(root);
        ll product = (total_sum - subtree_sum) * subtree_sum;
        max_product = max(max_product, product);

        dfs(root->left);
        dfs(root->right);
    }
public:
    int maxProduct(TreeNode* root) {
        total_sum = accum(root);
        dfs(root);
        return max_product % mod;
    }
};