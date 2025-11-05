typedef long long ll;
typedef pair<ll, ll> pll;

class Helper {
    int x;
    ll result;
    set<pll> top_x, bottom_kx;
    unordered_map<ll, ll> freq;
public:
    Helper(int x) {
        this->x = x;
        this->result = 0;
    }

    void insert(int num) {
        if (freq[num])
            internal_remove({freq[num], num});
        ++freq[num];
        internal_insert({freq[num], num});
    }

    void remove(int num) {
        internal_remove({freq[num], num});
        --freq[num];
        if (freq[num])
            internal_insert({freq[num], num});
    }

    ll get() { return result; }
private:
    void internal_insert(const pll& p) {
        if (top_x.size() < x) {
            top_x.insert(p);
            result += (p.first * p.second);
        }
        else if (p < *top_x.begin())
            bottom_kx.insert(p);
        else {
            bottom_kx.insert(*top_x.begin());
            result -= (top_x.begin()->first * top_x.begin()->second);
            top_x.erase(top_x.begin());
            top_x.insert(p);
            result += (p.first * p.second);
        }
    }
    void internal_remove(const pll& p) {
        if (p < *top_x.begin())
            bottom_kx.erase(p);
        else {
            top_x.erase(p);
            result -= (p.first * p.second);
            if (bottom_kx.size()) {
                top_x.insert(*bottom_kx.rbegin());
                result += (bottom_kx.rbegin()->first * bottom_kx.rbegin()->second);
                bottom_kx.erase(*bottom_kx.rbegin());
            }
        }
    }
};
class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<ll> ans(n - k + 1);
        Helper helper(x);
        for (int i = 0; i < n; ++i) {
            helper.insert(nums[i]);
            if (i >= k)
                helper.remove(nums[i-k]);
            if (i >= k-1)
                ans[i-k+1] = helper.get();
        }
        return ans;
    }
};