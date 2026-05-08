#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v)                                                           \
    do {                                                                       \
        cout << #v << " is |";                                                 \
        for (auto e : v)                                                       \
            cout << e << "|";                                                  \
        cout << endl;                                                          \
    } while (0)

class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    vector<ll> isPrime;
    vector<ll> primes;

    void eratosthenes(ll N) {
        isPrime.assign(N + 1, true);
        isPrime[0] = isPrime[1] = false;
        primes = {2};
        for (ll i = 4; i <= N; i += 2)
            isPrime[i] = false;
        for (ll i = 3; i <= N; i++) {
            if (isPrime[i])
                primes.push_back(i);
            for (ll j = i * i; j <= N; j += i * 2)
                isPrime[j] = false;
        }
    }

public:
    int minJumps(vector<int>& nums) {
        ll n = nums.size();
        vector<ll> visited(n, 0);
        eratosthenes(*max_element(nums.begin(), nums.end()));

        unordered_map<ll, vector<ll>> adj;
        for (ll i = 0; i < n; i++) {
            ll v = nums[i];
            if (isPrime[v]) {
                adj[v].push_back(i);
                continue;
            }

            for (ll j = 0; v > 1; j++)
                while (v % primes[j] == 0) {
                    v /= primes[j];
                    adj[primes[j]].push_back(i);
                }
        }

        queue<pll> q;
        q.push({0, 0});
        visited[0] = true;
        while (q.size()) {
            auto [idx, jumps] = q.front();
            q.pop();

            if (idx == n - 1) return jumps;

            ll v = nums[idx];

            if (idx > 0 && !visited[idx - 1]) {
                visited[idx - 1] = true;
                q.push({idx - 1, jumps + 1});
            }

            if (idx < n && !visited[idx + 1]) {
                visited[idx + 1] = true;
                q.push({idx + 1, jumps + 1});
            }

            if (isPrime[v]) {
                for (ll next : adj[v]) {
                    if (visited[next]) continue;
                    visited[next] = true;
                    q.push({next, jumps + 1});
                }
                adj[v].clear();
            }
        }

        return 0;
    }
};