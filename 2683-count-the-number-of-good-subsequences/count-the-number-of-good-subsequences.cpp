class Solution {
    typedef long long ll;
    const ll mod = 1e9 + 7;

    vector<ll> dp;
    ll combi(int n, int r) {
        if (n == r || r == 0) return 1;

        ll ret = fact(n);
        ret *= modinv(fact(r), mod);
        ret %= mod;
        ret *= modinv(fact(n-r), mod);
        ret %= mod;
        return ret;
    }
    ll fact(int n) {
        ll& ret = dp[n];
        if (ret) return ret;
        if (n == 0) return ret = 1;
        else if (n == 1) return ret = 1;
        return ret = n * fact(n - 1) % mod;
    }

    ll modinv(int a, int m) {
        ll x, y;
        exEuclid(a, m, x, y);
        return x;
    }
    ll exEuclid(ll a, ll b, ll &s, ll &t) {
        if (b == 0) {
            s = 1; t = 0;
            return a;
        }
        ll gcd = exEuclid(b, a%b, s, t);
        ll temp = t;
        t = s - (a / b)*t;
        s = temp;

        if (s <= 0) {
            s += b;
            t -= a;
        }
        return gcd;
    }
public:
    int countGoodSubsequences(string s) {
        vector<ll> freq(26, 0);
        ll maxfreq = 0;
        for (char c: s)
            maxfreq = max(maxfreq, ++freq[c - 'a']);

        dp.resize(s.size() + 1, 0);
        ll ret = 0;
        
        for (int k = 1; k <= maxfreq; k++) {
            ll count_subseq_k = 1;
            for (int i = 0; i < 26; i++) {
                if (freq[i] < k) continue;

                count_subseq_k *= (1 + combi(freq[i], k));
                count_subseq_k %= mod;
            }

            ret += (count_subseq_k - 1);
            ret %= mod;
        }
        return ret;
    }
};