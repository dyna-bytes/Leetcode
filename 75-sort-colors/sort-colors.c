
#define swap(a, b) do { \
    int t = a; \
    a = b; \
    b = t; \
} while (0)
void sortColors(int* nums, int numsSize) {
    int n = numsSize;

    int lo = 0, mid = 0, hi = n -1;
    while (mid <= hi) {
        if (nums[mid] == 0) {
            swap(nums[lo], nums[mid]);
            lo++, mid++;
        } else if (nums[mid] == 1)
            mid++;
        else if (nums[mid] == 2) {
            swap(nums[mid], nums[hi]);
            hi--;
        }
    }
}

/*
 * lo = 0, mid = 0, hi = n - 1
 * [2, 0, 2, 1, 1, 0]
 * 
*/