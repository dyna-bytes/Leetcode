class Container {
    typedef long long ll;

    ll k;
    ll sum;
    multiset<ll> st1, st2;
public:
    Container(int k) {
        this->k = k;
        sum = 0;
    }

    void rebalance() {
        while (st1.size() < k && st2.size() > 0) {
            int x = *(st2.begin());
            st1.insert(x);
            sum += x;
            st2.erase(st2.begin());
        }
        while (st1.size() > k) {
            int x = *prev(st1.end());
            st2.insert(x);
            st1.erase(prev(st1.end()));
            sum -= x;
        }
    }

    void add(int x) {
        if (st2.size() && x >= *(st2.begin())) {
            st2.insert(x);
        } else {
            st1.insert(x);
            sum += x;
        }

        rebalance();
    }

    void erase(int x) {
        auto it = st1.find(x);
        if (it != st1.end()) {
            st1.erase(it);
            sum -= x;
        } else {
            st2.erase(st2.find(x));
        }

        rebalance();
    }

    ll get_sum() { return sum; }
};

class Solution {
    typedef long long ll;
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        Container cont(k - 2);
        for (int i = 1; i < k - 1; i++)
            cont.add(nums[i]);

        ll ans = cont.get_sum() + nums[k - 1];
        for (int i = k; i < n; i++) {
            int j = i - dist - 1;
            if (j > 0)
                cont.erase(nums[j]);
            cont.add(nums[i - 1]);
            ans = min(ans, cont.get_sum() + nums[i]);
        }
        return ans + nums[0];
    }
};