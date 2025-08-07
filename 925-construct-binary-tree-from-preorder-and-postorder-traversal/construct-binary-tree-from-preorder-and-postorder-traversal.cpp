#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)
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
    TreeNode* devnconq(int s0, int e0, int s1, int e1, vector<int>& preorder, vector<int>& postorder) {
        if (s0 >= e0 || s1 >= e1) return nullptr;

        TreeNode *ret = new TreeNode();
        int root = preorder[s0];
        // debug(root);
        assert(root == postorder[e1 - 1]);
        ret->val = root;

        int size = e0 - s0;
        assert(size == e1 - s1);

        if (size == 1) return ret;
        
        int l1, r0;
        int left = preorder[s0 + 1];
        // debug(left);
        for (l1 = s1; l1 < e1; l1++) 
            if (postorder[l1] == left) break;
        // debug(l1);

        int right = postorder[e1 - 2];
        // debug(right);
        for (r0 = e0 - 1; r0 >= s0; r0--)
            if (preorder[r0] == right) break;
        // debug(r0);

        if (left == right) {
            ret->left = devnconq(s0 + 1, e0, s1, e1 - 1, preorder, postorder);
            return ret;
        }

        ret->left = devnconq(s0 + 1, r0, s1, l1 + 1, preorder, postorder);
        ret->right = devnconq(r0, e0, l1 + 1, e1 - 1, preorder, postorder);
        return ret;
    }
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size();
        
        return devnconq(0, n, 0, n, preorder, postorder);
    }
};