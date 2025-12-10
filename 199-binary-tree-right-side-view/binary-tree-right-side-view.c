/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MAX_SIZE (100 * 100)
int* rightSideView(struct TreeNode* root, int* returnSize) {
    int* ret = calloc(101, sizeof(int));
    *returnSize = 0;
    if (!root) return ret;
    
    struct TreeNode* q[MAX_SIZE] = {};
    int dq = 0;
    int eq = 0;
    q[++eq] = root;

    while (dq < eq) {
        int qsize = eq - dq;
        for (int i = 0; i < qsize; i++) {
            struct TreeNode* curr = q[++dq];
            if (i == qsize - 1) 
                ret[(*returnSize)++] = curr->val;

            if (curr->left)
                q[++eq] = curr->left;
            if (curr->right)
                q[++eq] = curr->right;
        }
    }

    return ret;
}