class Solution {
    int mirror(int n) {
        int x = 0;
        while (n > 0) {
            x *= 10;
            x += n % 10;
            n /= 10;
        }
        return x;
    }    
public:
    int mirrorDistance(int n) {
        return abs(n - mirror(n));
    }
};