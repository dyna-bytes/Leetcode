#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int reverseBits(int n) {
        bitset<32> b(n);
        bitset<32> r;
        for (int i = 0; i < 32; i++)
            r[31 - i] = b[i];

        return r.to_ulong();
    }
};