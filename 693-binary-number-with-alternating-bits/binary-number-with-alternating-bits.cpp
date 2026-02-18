class Solution {
#define debug(x) cout << #x << " is " << x << endl;
static inline unsigned int flz(unsigned int x) {
    return (sizeof(unsigned int) * 8 - __builtin_clz(x));
}
public:
    bool hasAlternatingBits(int n) {
        int msb = flz(n);
        int z = (1 & n);
        for (int i = 1; i < msb; ++i) {
            int x = (n >> i) & 1;           
            if (x == z) return false;
            z = x;
        }

        return true;
    }
};