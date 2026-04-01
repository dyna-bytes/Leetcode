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
    const int FALSE = 0;
    const int TRUE = 1;
    const int OR = 2;
    const int AND = 3;
    const int XOR = 4;
    const int NOT = 5;

    unordered_map<TreeNode*, int> dp_f, dp_g;

    int f(TreeNode* curr) { // minimum flips to make result true
        int op = curr->val;
        TreeNode* l = curr->left;
        TreeNode* r = curr->right;

        if (dp_f.count(curr)) return dp_f[curr];

        int ret = 0;
        if (op == FALSE || op == TRUE) { 
            ret = !op;
        } else if (op == OR) {
            ret = min({ f(l) + f(r), f(l) + g(r), g(l) + f(r) });
        } else if (op == AND) {
            ret = f(l) + f(r);
        } else if (op == XOR) {
            ret = min({ f(l) + g(r), g(l) + f(r) });
        } else if (op == NOT) {
            if (l) ret = g(l);
            else if (r) ret = g(r);
        }

        return dp_f[curr] = ret;
    }

    int g(TreeNode* curr) { // minimum flips to make result false
        int op = curr->val;
        TreeNode* l = curr->left;
        TreeNode* r = curr->right;

        if (dp_g.count(curr)) return dp_g[curr];

        int ret = 0;
        if (op == FALSE || op == TRUE) { 
            ret = op;
        } else if (op == OR) {
            ret = g(l) + g(r);
        } else if (op == AND) {
            ret = min({ f(l) + g(r), g(l) + f(r), g(l) + g(r) });
        } else if (op == XOR) {
            ret = min({ f(l) + f(r), g(l) + g(r) });
        } else if (op == NOT) {
            if (l) ret = f(l);
            else if (r) ret = f(r);
        }

        return dp_g[curr] = ret;
    }   
public:
    int minimumFlips(TreeNode* root, bool result) {
        if (result) return f(root);
        else return g(root);
    }
};