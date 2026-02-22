class Solution {
public:
    int binaryGap(int n) {
        if (__builtin_popcount(n) <= 1) return 0;

        int msb =  32 - __builtin_clz(n);
        int max_len = 0;
        for (int i = 0, j = 0; i < msb; ++i) {
            int x = (n >> i) & 1;
            if (x == 1) {
                for (j = i + 1; j < msb; ++j) {
                    int y = (n >> j) & 1;
                    if (y == 1) break;
                }

                max_len = max(max_len, j - i);
            }
        }
        return max_len;
    }
};