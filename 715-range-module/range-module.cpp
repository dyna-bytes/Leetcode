// #define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "] " << #x << " is " << x << endl;
#else
#define debug(x)
#endif

class RangeModule {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    #define LEFT    first
    #define RIGHT   second

    map<ll, ll> mp;
public:
    RangeModule() {
    }
    
    void addRange(int left, int right) {
        auto it = mp.upper_bound(left);
        
        if (it != mp.begin()) --it;
        ll minL = left;
        ll maxR = right;
        while (it != mp.end() && it->LEFT <= right) {
            if (it->RIGHT < left) {
                it++;
                continue;
            };

            minL = min(minL, it->LEFT);
            maxR = max(maxR, it->RIGHT);
            it = mp.erase(it);
        }

        mp.insert({minL, maxR});
    }
    
    bool queryRange(int left, int right) {
        if (mp.empty()) return false;
        auto it = mp.upper_bound(left);
        if (it != mp.begin()) --it;
        return (it->LEFT <= left && it->RIGHT >= right);
    }
    
    void removeRange(int left, int right) {
        auto it = mp.upper_bound(left);
        set<pll> to_add;

        if (it != mp.begin()) --it;
        while (it != mp.end() && it->LEFT < right) {
            if (it->RIGHT < left) {
                it++;
                continue;
            };

            if (it->LEFT < left) to_add.insert({it->LEFT, left});
            if (it->RIGHT > right) to_add.insert({right, it->RIGHT});
            it = mp.erase(it);
        }

        for (auto& interval: to_add) mp.insert(interval);
    }
};

/**
 * Your RangeModule object will be inmpantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */