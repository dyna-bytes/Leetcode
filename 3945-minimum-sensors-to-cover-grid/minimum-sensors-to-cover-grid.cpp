class Solution {
public:
    int minSensors(int n, int m, int k) {
        int s = 2 * k + 1;
        int ceil_n = n / s + (bool)(n % s);
        int ceil_m = m / s + (bool)(m % s);

        return ceil_n * ceil_m;
    }
};