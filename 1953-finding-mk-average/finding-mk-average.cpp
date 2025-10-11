#define debug(x) cout << #x << " is " << x << endl;
class MKAverage {
    int m, k;
    long long mid_sum;
    queue<int> q;
    multiset<int> lo, mid, hi;
    void insert(int num) {
        if (lo.size() < k || num <= *lo.rbegin())
            lo.insert(num);
        else if (hi.size() < k || num < *hi.begin()) {
            mid.insert(num);
            mid_sum += num;
        } else
            hi.insert(num);
    }

    int remove(int x) {
        auto it = lo.find(x);
        if (it != lo.end()) {
            lo.erase(it);
            return 0;
        } 

        it = mid.find(x);
        if (it != mid.end()) {
            mid.erase(it);
            mid_sum -= x;
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
        while (lo.size() < k && !mid.empty()) {
            lo.insert(*mid.begin());
            mid_sum -= *mid.begin();
            mid.erase(mid.begin());
        }
        while (hi.size() < k && !mid.empty()) {
            hi.insert(*mid.rbegin());
            mid_sum -= *mid.rbegin();
            mid.erase(prev(mid.end()));
        }
    }
public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
        mid_sum = 0;
    }

    
    void addElement(int num) {
        q.push(num);
        insert(num);

        if (q.size() > m) {
            remove(q.front());
            q.pop();
        }
        if (q.size() >= m) {
            rebalance();
        }
    }
    
    int calculateMKAverage() {
        if (q.size() < m) return -1;
        return mid_sum / (m - 2*k); 
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */