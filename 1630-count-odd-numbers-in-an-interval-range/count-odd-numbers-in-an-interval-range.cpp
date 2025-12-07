class Solution {
public:
    int countOdds(int low, int high) {
        if ((low & 1) && (high & 1)) {
            int n = (high - low + 1) / 2;
            return n + 1;
        } else if ((low & 1)) {
            int n = (high - low + 1) / 2;
            return n;
        } else if ((high & 1)) {
            int n = (high - low + 1) / 2;
            return n;
        } else {
            int n = (high - low + 1) / 2;
            return n;
        }

        return -1;
    }
};