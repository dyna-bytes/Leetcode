typedef long long ll;
bool isPowerOfTwo(int n) {
    if (n == 0) return false;
    ll x = n;
    return (x & (x - 1)) == 0;
}