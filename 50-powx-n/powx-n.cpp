class Solution {
public:
    double myPow(double x, int n) {
        if (n < 0) return 1 / myPow(x, -(long long)n);
        return myPow(x, (long long)n);
    }
    double myPow(double x, long long n) {
        /*
        * x^n = x^(n/2) * x^(n/2)
        */

        if (n == 1) return x;
        if (n == 0) return 1;

        double square = myPow(x, n/2);
        if (n & 1) return square * square * x;
        return square * square;
    }
};