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
    unordered_map<TreeNode*, int> dp_num;
    unordered_map<TreeNode*, int> dp_sum;

    int number_dfs(TreeNode* curr) {
        if (!curr) return 0;
        if (dp_num.count(curr)) return dp_num[curr];

        int ret = 1;
        ret += number_dfs(curr->left);
        ret += number_dfs(curr->right);
        return dp_num[curr] = ret;        
    }

    int sum_dfs(TreeNode* curr) {
        if (!curr) return 0;
        if (dp_sum.count(curr)) return dp_sum[curr];

        int ret = curr->val;
        ret += sum_dfs(curr->left);
        ret += sum_dfs(curr->right);
        return dp_sum[curr] = ret;
    }

    int check_dfs(TreeNode* curr) {
        if (!curr) return 0;

        int ret = 0;
        if (curr->val == sum_dfs(curr) / number_dfs(curr))
            ret++;
        
        ret += check_dfs(curr->left);
        ret += check_dfs(curr->right);
        return ret;
    }
public:
    int averageOfSubtree(TreeNode* root) {
        return check_dfs(root);

    }
};