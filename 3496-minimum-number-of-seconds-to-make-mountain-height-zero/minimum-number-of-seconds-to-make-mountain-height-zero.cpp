#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;

class Solution {
    typedef long long ll;
    const ll INF = 1e16;
    int mountainHeight;
    vector<int> workerTimes;
    ll workerTimesSum;

    ll search(int idx, ll t) {
        auto fit = [&](int i, ll x) {
            return workerTimes[i] * x * (x + 1) / 2 <= t;
        };

        ll l = 0, r = mountainHeight + 1; 
        while (l + 1 < r) {
            ll m = (l + r) / 2;
            if (fit(idx, m)) l = m;
            else r = m;
        }
        return l;
    }

    bool work(ll t) {
        ll sum = 0;
        for (int i = 0; i < workerTimes.size(); i++) {
            ll x = search(i, t);
            sum += x;
        }

        return sum >= mountainHeight;
    }
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        this->mountainHeight = mountainHeight;
        this->workerTimes = workerTimes;

        ll l = 0, r = INF;

        while (l + 1 < r) {
            ll m = (l + r) / 2;
            if (work(m)) r = m;
            else l = m;
        }
        return l + 1;
    }
};