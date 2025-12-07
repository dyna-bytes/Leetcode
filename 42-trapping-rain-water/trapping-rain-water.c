#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int trap(int* height, int heightSize) {
    int n = heightSize;
    int* left = calloc(n, sizeof(int));
    int* right = calloc(n, sizeof(int));

    left[0] = height[0];
    for (int i = 1; i < n; i++)
        left[i] = max(left[i - 1], height[i]);
    
    right[n-1] = height[n-1];
    for (int i = n-2; i >= 0; i--)
        right[i] = max(right[i + 1], height[i]);

    int fill = 0;
    for (int i = 0; i < n; i++)
        fill += min(left[i], right[i]) - height[i];
    return fill;
}