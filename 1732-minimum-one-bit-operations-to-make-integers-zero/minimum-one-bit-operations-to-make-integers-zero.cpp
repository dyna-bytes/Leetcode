#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    int f(int n, int bitsize) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        int lsb = 1 << (bitsize - 1);
        if (n == lsb) return 2*n - 1;

        return f(lsb, bitsize) - f(n - lsb, floor(log2(n - lsb)) + 1);
    }
public:
    int minimumOneBitOperations(int n) {
        if (n == 0) return 0;
        return f(n, floor(log2(n)) + 1);
    }
};