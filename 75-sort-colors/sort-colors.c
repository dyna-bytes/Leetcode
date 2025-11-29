
#define swap(a, b) do { \
    int t = a; \
    a = b; \
    b = t; \
} while (0)
void sortColors(int* nums, int numsSize) {
    int n = numsSize;

    int* count = calloc(3, sizeof(int));
    for (int i = 0; i < n; i++) 
        count[nums[i]]++;
    
    int i = 0;
    for (int c = 0; c < 3; c++) {
        for (int t = 0; t < count[c]; t++)
            nums[i++] = c;
    }
}

/*
 * [2, 0, 2, 1, 1, 0]
 * [0, 0, 2, 1, 1, 2]
 * [0, 0, 1, 1, 2, 2]
*/