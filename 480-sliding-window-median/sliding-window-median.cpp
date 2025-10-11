#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef long long ll;
    int k;
    int lo_size;
    int hi_size;
    multiset<ll> lo, hi; // lo.size = round_up(k/2), hi.size = round_down(k/2)

    void rebalance() {
        while (lo.size() > lo_size) {
            hi.insert(*lo.rbegin());
            lo.erase(--lo.end());
        }
        while (hi.size() > hi_size) {
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }
    }

    void shuffle() {
        while (*lo.rbegin() > *hi.begin()) {
            ll lo_top = *lo.rbegin();
            ll hi_btm = *hi.begin();

            lo.erase(--lo.end());
            hi.erase(hi.begin());

            lo.insert(hi_btm);
            hi.insert(lo_top);
        }
    }

    void moveStream(ll in, ll out = LONG_LONG_MIN) {
        // insertion to lo or hi
        if (hi.size() < hi_size || in < *hi.begin())
            lo.insert(in);
        else
            hi.insert(in);

        // pop out 
        if (out != LONG_LONG_MIN) {
            auto it = lo.find(out);
            if (it != lo.end()) 
                lo.erase(it);
            else {
                it = hi.find(out);
                hi.erase(it);
            }
        }

        // rebalance
        if (lo.size() + hi.size() == lo_size + hi_size)
            rebalance();

        // shuffle
        if (lo.size() && hi.size())
            shuffle();
    }
    double getMedian() {
        if (lo_size == hi_size + 1)
            return *lo.rbegin();
        return (double)(*lo.rbegin() + *hi.begin())/2;
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        this->k = k;
        lo_size = k/2 + !!(k & 1);
        hi_size = k/2;

        vector<double> ret(nums.size() - k + 1, 0);

        for (int i = 0; i < k; i++)
            moveStream(nums[i]);

        for (int i = k; i < nums.size(); i++) {
            ret[i-k] = getMedian();
            moveStream(nums[i], nums[i-k]);
        }
        ret[ret.size() - 1] = getMedian();
        return ret;
    }
};