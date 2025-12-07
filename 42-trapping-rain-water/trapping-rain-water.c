#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int trap(int* height, int heightSize) {
    int n = heightSize;
    int* stck = calloc(n + 1, sizeof(int)); // monotone decreasing stack. holds previous greater number
    int sp = 0;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (sp && height[stck[sp]] < height[i]) {
            int curr_top = stck[sp]; // local minimum
            sp--;
            if (sp == 0) break;

            int prev_top = stck[sp]; // previous greater height
            int bound_height = min(height[i], height[prev_top]) - height[curr_top];
            int dist = i - prev_top - 1;
            ans += (bound_height * dist);
        }

        stck[++sp] = i;
    }
    return ans;
}