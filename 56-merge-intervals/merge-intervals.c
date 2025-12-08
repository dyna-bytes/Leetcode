/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define swap(A, B) do { \
    char _tmp[sizeof((A))]; \
    memcpy(_tmp, &(A), sizeof((A))); \
    memcpy(&(A), &(B), sizeof((A))); \
    memcpy(&(B), _tmp, sizeof((A))); \
} while (0)
#define max(a, b) ((a) > (b) ? (a) : (b))

bool cmp(int* l_int, int* r_int) {
    if (l_int[0] == r_int[0]) return l_int[1] < r_int[1];
    return l_int[0] < r_int[0];
}

void sort(int s, int e, int** intervals) {
    if (s + 1 >= e) return;

    int m = (s + e) / 2;
    sort(s, m, intervals);
    sort(m, e, intervals);

    int l = s;
    int r = m;
    int k = 0;

    int* buf[(1 << 14)];

    for (; l < m && r < e; ) {
        if (cmp(intervals[l], intervals[r]))
            buf[k++] = intervals[l++];
        else 
            buf[k++] = intervals[r++];
    }

    while (l < m)
        buf[k++] = intervals[l++];
    while (r < e)
        buf[k++] = intervals[r++];

    for (int i = 0; i < k; i++)
        intervals[s + i] = buf[i];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    int n = intervalsSize;

    sort(0, n, intervals);
    
    int** ret = calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
        ret[i] = calloc(2, sizeof(int));
    
    *returnSize = 0;
    *returnColumnSizes = calloc(n, sizeof(int*));
    for (int i = 0, j = 0; i < n; i++) {
        // printf("[%d %d] ", intervals[i][0], intervals[i][1]);
        bool overlapped = false;
        int max_end = intervals[i][1];
        for (j = i + 1; j < n && max_end >= intervals[j][0]; j++) {
            overlapped = true;
            max_end = max(max_end, intervals[j][1]);
        }
        
        if (overlapped) {
            ret[*returnSize] = calloc(2, sizeof(int));
            (*returnColumnSizes)[*returnSize] = 2;

            ret[*returnSize][0] = intervals[i][0];
            ret[*returnSize][1] = max_end;
            (*returnSize)++;

            i = j - 1;
        } else {
            ret[*returnSize] = calloc(2, sizeof(int));
            (*returnColumnSizes)[*returnSize] = 2;

            ret[*returnSize][0] = intervals[i][0];
            ret[*returnSize][1] = intervals[i][1];
            (*returnSize)++;
        }
    }

    return ret;
}