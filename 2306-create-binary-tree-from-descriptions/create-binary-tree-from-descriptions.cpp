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
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> um;
        unordered_map<TreeNode*, TreeNode*> parent;

        for (auto& desc: descriptions) {
            int p = desc[0], c = desc[1], isLeft = desc[2];

            if (um.count(p) == 0) um[p] = new TreeNode(p);
            if (um.count(c) == 0) um[c] = new TreeNode(c);

            if (isLeft) um[p]->left = um[c];
            else um[p]->right = um[c];

            parent[um[c]] = um[p];
        }

        for (auto& [val, node]: um) {
            if (parent.count(node) == 0)
                return node;
        }
        return nullptr;
    }
};