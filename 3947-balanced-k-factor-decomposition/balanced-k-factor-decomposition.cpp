#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto n: v) cout << n << "|";\
    cout << endl; \
} while (0)

class Solution {
    typedef long long ll;
    ll minDiff;
    vector<int> primes;
    vector<int> candi;
    vector<int> res;
    void dfs(int curr) {
        if (curr >= primes.size()) {
            ll minE = *min_element(candi.begin(), candi.end());
            ll maxE = *max_element(candi.begin(), candi.end());
            if (minDiff > maxE - minE) {
                minDiff = maxE - minE;
                res = candi;
            }
            return;
        }
        
        for (int i = 0; i < candi.size(); i++) {
            if (i > 0 && candi[i] == candi[i-1]) continue;
            candi[i] *= primes[curr];
            dfs(curr + 1);
            candi[i] /= primes[curr];
        }
    }
public:
    vector<int> minDifference(int n, int k) {
        for (int i = 2; i * i <= n; i++) {
            while (n % i == 0) {
                primes.push_back(i);
                n /= i;
            }
        }

        if (n > 1)
            primes.push_back(n);
        
        sort(primes.begin(), primes.end());
        candi.resize(k, 1);
        minDiff = INT_MAX;
        dfs(0);
        return res;
    }
};