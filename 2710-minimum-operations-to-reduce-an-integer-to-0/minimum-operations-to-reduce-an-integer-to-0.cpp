#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int minOperations(int n) {
        bitset<32> b(n);
        int cnt = 0;

        for (int i = 0, j = 0; i < 32; i++) {
            if (b[i] == 0) continue;
            for (j = i + 1; j < 32 && b[j] == 1; j++) {}

            int seg = j - i;
            if (seg >= 2) {
                b = b.to_ulong() + (1 << i);
                cnt++;
            }
            i = j - 1;
        }

        return cnt + b.count();
    }
};