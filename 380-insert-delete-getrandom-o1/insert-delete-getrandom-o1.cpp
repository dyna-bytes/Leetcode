class RandomizedSet {
    unordered_map<int, int> um; // { val : index }
    vector<int> v; 
public:
    RandomizedSet() {
    }
    
    bool insert(int x) {
        if (um.count(x)) return false;
        
        v.push_back(x);
        um[x] = v.size() - 1;
        return true;
    }
    
    bool remove(int x) {
        if (um.count(x) == 0) return false;

        int idx_x = um[x];
        int idx_y = v.size() - 1;
        int y = v[idx_y];

        v[idx_x] = v[idx_y];
        um[y] = idx_x;

        v.pop_back();
        um.erase(x);
        return true;
    }
    
    int getRandom() {
        return v[random() % v.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */