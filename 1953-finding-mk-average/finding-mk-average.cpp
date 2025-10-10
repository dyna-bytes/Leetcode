class MKAverage {
    int m, k;
    long long mid_sum = 0;
    queue<int> q;
    multiset<int> left, mid, right;
    bool remove_from_set(multiset<int>& ms, int x) {
        auto it = ms.find(x);
        if (it == ms.end()) return false;
        ms.erase(it);
        return true;
    }

    void rebalance_pull_left() {
        while (left.size() < k) {
            auto it = mid.begin();
            left.insert(*it);
            mid_sum -= *it;
            mid.erase(it);
        }

        while (mid.size() < m - 2*k) {
            auto it = right.begin();
            mid.insert(*it);
            mid_sum += *it;
            right.erase(it);
        }  
    }

    void rebalance_push_right() {
        while (left.size() > k) {
            auto it = --left.end();
            mid.insert(*it);
            mid_sum += *it;
            left.erase(it);
        }

        while (mid.size() > m - 2*k) {
            auto it = --mid.end();
            right.insert(*it);
            mid_sum -= *it;
            mid.erase(it);
        }
    }
public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
    }
    
    void addElement(int num) {
        if (q.size() >= m) {
            int x = q.front();
            q.pop();

            if (remove_from_set(left, x)) ;
            else if (remove_from_set(right, x)) ;
            else if (remove_from_set(mid, x)) mid_sum -= x;
            rebalance_pull_left();
        }
        q.push(num);
        left.insert(num);
        rebalance_push_right();
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