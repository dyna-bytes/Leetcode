/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define RANGE 10000
#define SIZE (2*RANGE + 1)
#define PUT_FIRST(count, i, x) (count[i + RANGE][0] = x)
#define GET_FIRST(count, i) (count[i + RANGE][0])
#define PUT_SECOND(count, i, x) (count[i + RANGE][1] = x)
#define GET_SECOND(count, i) (count[i + RANGE][1])

int cmp(const void* a, const void* b) {
    int* x = (int*)a;
    int* y = (int*)b;
    return y[0] - x[0];
}
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int* ret = calloc(k, sizeof(int));
    *returnSize = k;

    int count[SIZE][2];
    memset(count, 0, sizeof(count));
    int n = numsSize;
    for (int i = 0; i < n; i++) {
        PUT_FIRST(count, nums[i], GET_FIRST(count, nums[i]) + 1);
        PUT_SECOND(count, nums[i], nums[i]);
    }

    qsort(count, SIZE, sizeof(int*), cmp);

    for (int i = 0; i < k; i++)
        ret[i] = count[i][1];
    return ret;
}