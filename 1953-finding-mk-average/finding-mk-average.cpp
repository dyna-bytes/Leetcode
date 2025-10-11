class MKAverage {
    int m, k;
    long long mid_sum = 0;
    queue<int> q;
    multiset<int> lo, mid, hi;

    int remove(int x) {
        auto it = lo.find(x);
        if (it != lo.end()) {
            lo.erase(it);
            return 0;
        } 

        it = mid.find(x);
        if (it != mid.end()) {
            mid_sum -= *it;
            mid.erase(it);
            return 0;
        }
        
        it = hi.find(x);
        if (it != hi.end()) {
            hi.erase(it);
            return 0;
        }
        return -1;
    }
    void rebalance() {
        while (lo.size() < k && mid.size()) {
            lo.insert(*mid.begin());
            mid_sum -= *mid.begin();
            mid.erase(mid.begin());
        }
        while (hi.size() < k && mid.size()) {
            hi.insert(*mid.rbegin());
            mid_sum -= *mid.rbegin();
            mid.erase(--mid.end());
        }
        while (lo.size() > k) {
            mid.insert(*lo.rbegin());
            mid_sum += *lo.rbegin();
            lo.erase(--lo.end());
        }
        while (hi.size() > k) {
            mid.insert(*hi.begin());
            mid_sum += *hi.begin();
            hi.erase(hi.begin());
        }
    }
    void shuffle() {
        while (lo.size() && mid.size() && *lo.rbegin() > *mid.begin()) {
            int lo_top = *lo.rbegin();
            int mid_btm = *mid.begin();

            lo.erase(--lo.end());
            mid.erase(mid.begin());
            mid_sum -= mid_btm;

            lo.insert(mid_btm);
            mid.insert(lo_top);
            mid_sum += lo_top;
        }

        while (mid.size() && hi.size() && *mid.rbegin() > *hi.begin()) {
            int mid_top = *mid.rbegin();
            int hi_btm = *hi.begin();

            mid.erase(--mid.end());
            mid_sum -= mid_top;
            hi.erase(hi.begin());

            mid.insert(hi_btm);
            mid_sum += hi_btm;
            hi.insert(mid_top);
        }
    }
public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
    }
    
    void addElement(int num) {
        q.push(num);
        mid.insert(num);
        mid_sum += num;

        if (q.size() > m) {
            remove(q.front());
            q.pop();
        }

        if (q.size() == m) {
            rebalance();
            shuffle();
        }
    }
    
    int calculateMKAverage() {
        if (q.size() < m) return -1;
        return mid_sum / (m - 2 * k);
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */