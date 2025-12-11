/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* preorder(struct TreeNode* curr) {
    // printf("%d\n", curr->val);
    if (curr->left) {
        struct TreeNode* tail = preorder(curr->left);
        if (curr->right) 
            tail->right = curr->right;
        
        curr->right = curr->left;
        curr->left = NULL;
        if (tail->right)
            return preorder(tail->right);
        return tail;
    } 

    if (curr->right)
        return preorder(curr->right);

    return curr;
}
void flatten(struct TreeNode* root) {
    if (!root) return;
    preorder(root);
}