/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MAX_SIZE 100000
typedef struct {
    int val;
    int idx;
} pair;
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int n = numsSize;
    int* ret = calloc(n - k + 1, sizeof(int));
    (*returnSize) = 0;
    
    pair q[MAX_SIZE] = {};
    int eq = 0;
    int dq = 0;

    for (int i = 0; i < k; i++) {
        while (dq <= eq && q[eq].val < nums[i])
            eq--;

        pair p = { nums[i], i };
        q[++eq] = p;
    }


    for (int i = k; i < n; i++) {
        ret[(*returnSize)++] = q[dq].val;

        while (dq <= eq && q[dq].idx < i - k + 1)
            dq++;
        
        while (dq <= eq && q[eq].val < nums[i])
            eq--;


        pair p = { nums[i], i };
        q[++eq] = p;
    }

    if (dq <= eq)
        ret[(*returnSize)++] = q[dq].val;

    return ret;
}