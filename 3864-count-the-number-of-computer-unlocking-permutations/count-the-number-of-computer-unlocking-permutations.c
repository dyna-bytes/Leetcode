#define min(a, b) (a) < (b) ? (a) : (b)
typedef long long ll;
const ll mod = 1e9 + 7;

ll fact(ll n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    return n * fact(n - 1) % mod;
}
int countPermutations(int* complexity, int complexitySize) {
    int n = complexitySize;
    int mincplx = complexity[0];
    for (int i = 1; i < n; i++)
        if (mincplx >= complexity[i]) return 0;

    return fact(n-1);
}