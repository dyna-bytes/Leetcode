#define debug(x) printf("%s is %d\n", #x, x);

int countMajoritySubarrays(int* nums, int numsSize, int target) {
    int ret = 0;
    int* pref = calloc(numsSize + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++) 
        pref[i + 1] = pref[i] + (nums[i] == target);

    for (int s = 0; s < numsSize; s++) {
        for (int e = s + 1; e <= numsSize; e++) {
            if (2 * (pref[e] - pref[s]) > e - s)
                ret++;
        }
    }
    return ret;
}