class MKAverage {
    int m, k;
    long long mid_sum;
    queue<int> q;
    multiset<int> left, mid, right;

    void deletingRebalance() {
        if (left.size() < k) {
            auto mid_bottom = mid.begin();
            left.insert(*mid_bottom);

            mid_sum -= *mid_bottom;
            mid.erase(mid_bottom);
        } else if (right.size() < k) {
            auto mid_top = --mid.end();
            right.insert(*mid_top);

            mid_sum -= *mid_top;
            mid.erase(mid_top);
        }
    }
    void insertingRebalance(int num) {
        auto left_top = --left.end();
        auto right_bottom = right.begin();
        if (num < *left_top) {
            left.insert(num);

            mid.insert(*left_top);
            mid_sum += *left_top;
            
            left.erase(left_top);
        } else if (num > *right_bottom) {
            right.insert(num);

            mid.insert(*right_bottom);
            mid_sum += *right_bottom;

            right.erase(right_bottom);
        } else {
            mid.insert(num);
            mid_sum += num;
        }
    }
public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
        mid_sum = 0;
    }
    
    void addElement(int num) {
        auto removeNum = [&] (multiset<int>& group, int x) {
            auto it = group.find(x);
            if (it == group.end()) return false;
            group.erase(it);
            return true;
        };

        q.push(num);
        if (q.size() < m) {
            mid.insert(num);
            mid_sum += num;
        } else if (q.size() == m) {
            mid.insert(num);
            mid_sum += num;

            // construct left and right.
            // left size = k
            // right size = k
            // mid size = m - 2k
            for (int i = 0; i < k; i++) {
                auto mid_bottom = mid.begin();

                left.insert(*mid_bottom);
                mid_sum -= *mid_bottom;
                mid.erase(mid_bottom);
            }

            for (int i = 0; i < k; i++) {
                auto mid_top = --mid.end();

                right.insert(*mid_top);
                mid_sum -= *mid_top;
                mid.erase(mid_top);
            }
        } else if (q.size() > m) {
            // left size = k
            // right size = k
            // mid size = m - 2k + 1
            insertingRebalance(num);

            int x = q.front(); q.pop();
            if (removeNum(mid, x)) // mid size = m - 2k, left size = right size = k
                mid_sum -= x;
            else if (removeNum(left, x)) ; // left size = k - 1, right size = k, mid size = m - 2k + 1
            else removeNum(right, x) ; // right size = k - 1, left size = k, mid size = m - 2k + 1
            
            deletingRebalance();
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