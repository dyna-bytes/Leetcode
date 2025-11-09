class Solution {
    typedef long long ll;
public:
    int reverse(int x) {
        if (x == 0) return 0;
        if (x == INT_MIN || x == INT_MAX) return 0;

        int sign = x / abs(x);

        ll y = 0;
        while (x) {
            y *= 10;
            y += x % 10;
            x /= 10;
        }

        y = sign * abs(y);
        if (y < INT_MIN || y > INT_MAX) return 0;
        return y;
    }
};