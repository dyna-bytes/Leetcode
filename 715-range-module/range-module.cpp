class RangeModule {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    set<pll> ranges;

    template <typename T>
    typename std::set<T>::iterator
    safe_prev(std::set<T>& s, typename std::set<T>::iterator it) {
        return (it == s.begin()) ? it : std::prev(it);
    }

    bool intersects(const pll& i1, const pll& i2) {
        return (i1.first <= i2.second && i2.first <= i1.second);
    }
    bool fullCover(const pll& large, const pll& small) {
        return (large.first <= small.first && large.second >= small.second);
    }
    pll overlapping(const pll& i1, const pll& i2) {
        // if (!intersects(i1, i2)) return {-1, -1};
        return {max(i1.first, i2.first), min(i1.second, i2.second)};
    }
    void debug() {
        for (auto range : ranges)
            cout << "[" << range.first << ", " << range.second << ") ";
        cout << endl;
    }

public:
    RangeModule() {}

    void addRange(int left, int right) {
        // cout << "add [" << left << ", " << right << ") " << endl;
        auto it = ranges.lower_bound({left, 0});

        if (it != ranges.begin()) {
            auto prv = prev(it);
            if (prv->second >= left)
                it = prv;
        }

        ll min_left = left;
        ll max_right = right;
        while (it != ranges.end() && it->first <= right) {
            auto nxt = next(it);
            if (it->second >= left) {
                min_left = min(min_left, it->first);
                max_right = max(max_right, it->second);
                ranges.erase(it);
            }
            it = nxt;
        }
        ranges.insert({min_left, max_right});
        // debug();
    }

    bool queryRange(int left, int right) {
        pll interval = {left, right};

        for (auto it = safe_prev(ranges, ranges.lower_bound(pll{left, 0}));
             it != ranges.end(); it++) {
            if (fullCover(*it, interval))
                return true;
        }
        return false;
    }

    void removeRange(int left, int right) {
        // cout << "remove [" << left << ", " << right << ") " << endl;

        pll interval = {left, right};
        // A. the removal-range entirely covers the range of an existing
        // interval.
        for (auto it = safe_prev(ranges, ranges.lower_bound(pll{left, 0}));
             it != ranges.end();) {
            auto nxt = next(it);
            if (fullCover(interval, *it))
                ranges.erase(it);
            it = nxt;
        }

        // B. the existing interval entirely covers the removal range.
        for (auto it = safe_prev(ranges, ranges.lower_bound(pll{left, 0}));
             it != ranges.end();) {
            auto nxt = next(it);
            if (fullCover(*it, interval)) {
                pll curr = *it;
                ranges.erase(it);

                if (curr.first < left) {
                    addRange(curr.first, left);
                }
                if (curr.second > right) {
                    addRange(right, curr.second);
                }

                break;
            }
            it = nxt;
        }

        // C. the existing range and the removal range intersect but don't fully
        // cover one or the other.
        for (auto it = safe_prev(ranges, ranges.lower_bound(pll{left, 0}));
             it != ranges.end();) {
            auto nxt = next(it);
            if (intersects(*it, interval)) {
                pll curr = *it;
                ranges.erase(it);

                if (curr.first < left) {
                    addRange(curr.first, left);
                    it = ranges.upper_bound(pll{left, 0});
                    continue;
                } else if (curr.second > right) {
                    addRange(right, curr.second);
                    break;
                }
            }
            it = nxt;
        }
        // debug();
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */