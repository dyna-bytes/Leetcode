void moveZeroes(int* nums, int numsSize) {
    int n = numsSize;
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) continue;
        nums[j++] = nums[i];
    }

    for (; j < n; j++)
        nums[j] = 0;
}