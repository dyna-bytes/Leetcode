int missingNumber(int* nums, int numsSize) {
    int x = 0;
    int n = numsSize;
    for (int i = 0; i <= n; i++)
        x ^= i;

    for (int i = 0; i < n; i++)
        x ^= nums[i];

    return x;
}