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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);

        int level = 1;
        int max_level = 0;
        int max_level_sum = INT_MIN;
        
        while (q.size()) {
            int qsize = q.size();
            int level_sum = 0;
            for (int i = 0; i < qsize; i++) {
                TreeNode* curr = q.front();
                q.pop();

                level_sum += curr->val;
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }

            if (max_level_sum < level_sum) {
                max_level_sum = level_sum;
                max_level = level;
            }

            level++;
        }
        return max_level;
    }
};