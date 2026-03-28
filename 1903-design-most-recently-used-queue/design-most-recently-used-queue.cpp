class MRUQueue {
    list<int> ls;
public:
    MRUQueue(int n) {
        for (int i = 1; i <= n; i++)
            ls.push_back(i);
    }
    
    int fetch(int k) {
        auto it = ls.begin();
        for (int i = 1; i < k; i++)
            it = next(it);

        int v = *it;
        ls.erase(it);
        ls.push_back(v);
        return v;
    }
};

/**
 * Your MRUQueue object will be instantiated and called as such:
 * MRUQueue* obj = new MRUQueue(n);
 * int param_1 = obj->fetch(k);
 */