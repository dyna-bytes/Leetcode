class Solution {
public:
    int bitwiseComplement(int n) {
        if (n == 0) return 1;
        int msb = 32 - __builtin_clz(n);
        int x = (1 << msb) - 1;
        return x - n;
    }
};