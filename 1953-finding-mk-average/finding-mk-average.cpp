class MKAverage {
    int m, k, sum = 0;
    queue<int> q;
    multiset<int> lo, mid, hi;
    void rebalance(int num) {
        if (num < *lo.rbegin()) {
            lo.insert(num);

            int x = *lo.rbegin();
            lo.erase(--lo.end());
            mid.insert(x);
            sum += x;
        } else if (num > *hi.begin()) {
            hi.insert(num);

            int x = *hi.begin();
            hi.erase(hi.begin());
            mid.insert(x);
            sum += x;
        } else {
            mid.insert(num);
            sum += num;
        }
    }
    void postRebalance(void) {
        if (lo.size() < k) {
            int x = *mid.begin();
            mid.erase(mid.begin());
            lo.insert(x);
            sum -= x;
        } else if (hi.size() < k) {
            int x = *mid.rbegin();
            mid.erase(--mid.end());
            hi.insert(x);
            sum -= x;
        }
    }
public:
    MKAverage(int m, int k) : m(m), k(k) {
    }
    
    void addElement(int num) {
        
        auto removeNum = [&](multiset<int>& ms, int n) {
            auto it = ms.find(n);
            if (it == ms.end()) return false;
            ms.erase(it);
            return true;
        };

        q.push(num);
        if (q.size() < m) mid.insert(num);
        else if (q.size() == m) {
            mid.insert(num);
            for (int i = 0; i < k; i++) {
                lo.insert(*mid.begin());
                mid.erase(mid.begin());
                hi.insert(*mid.rbegin());
                mid.erase(--mid.end());
            }
            for (int x : mid) sum += x;
        } else if (q.size() > m) {
            rebalance(num);

            int rm = q.front(); q.pop();
            if (removeNum(mid, rm))
                sum -= rm;
            else if (removeNum(lo, rm)) ;
            else removeNum(hi, rm) ;

            postRebalance();
        }
    }
    
    int calculateMKAverage() {
        if (q.size() < m) return -1;
        return sum / (m - 2*k);
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */