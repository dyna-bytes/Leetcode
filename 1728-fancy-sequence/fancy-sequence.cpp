class Fancy {
    typedef long long ll;
    const ll mod = 1e9 + 7;
    vector<ll> v, a, b;

    ll __pow(ll x, ll k) {
        if (k == 0) return 1;

        ll half = __pow(x, k >> 1);
        ll res = (half * half) % mod;
        if (k & 1)  return (res * x) % mod;        
        return res;
    }
    ll inv(ll x) {
        return __pow(x, mod - 2);
    }
public:
    Fancy() {
        a.push_back(1);
        b.push_back(0);
    }
    
    void append(int val) {
        v.push_back(val);
        a.push_back(a.back());
        b.push_back(b.back());
    }
    
    void addAll(int inc) {
        b.back() = (b.back() + inc) % mod;
    }
    
    void multAll(int m) {
        a.back() = a.back() * m % mod;
        b.back() = b.back() * m % mod;
    }
    
    int getIndex(int idx) {
        if (idx >= v.size()) return -1;
        ll a_old = inv(a[idx]) * a.back() % mod;
        ll b_old = (b.back() - b[idx] * a_old % mod + mod) % mod;
        return (a_old * v[idx] % mod + b_old) % mod;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->bAll(inc);
 * obj->aAll(m);
 * int param_4 = obj->getIndex(idx);
 */