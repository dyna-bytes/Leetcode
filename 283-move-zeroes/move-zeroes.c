void moveZeroes(int* nums, int numsSize) {
    int n = numsSize;
    int* ret = calloc(n, sizeof(int));
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) continue;
        ret[j++] = nums[i];
    }
    memcpy(nums, ret, n * sizeof(int));
    free(ret);
}