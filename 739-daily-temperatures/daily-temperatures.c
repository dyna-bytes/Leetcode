/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    int val;
    int idx;
} pair;
int* dailyTemperatures(int* temps, int tempsSize, int* retSize) {
    int n = tempsSize;
    pair stack[100000] = {}; // increasing monotonic stack from backward
    int sp = 0;

    *retSize = n;
    int* ret = calloc(n, sizeof(int));
    for (int i = n-1; i >= 0; i--) {
        while (sp > 0 && stack[sp].val <= temps[i])
            sp--;

        ret[i] = (sp == 0) ? 0 : stack[sp].idx - i;
        pair p = {temps[i], i};
        stack[++sp] = p;
    }

    return ret;
}