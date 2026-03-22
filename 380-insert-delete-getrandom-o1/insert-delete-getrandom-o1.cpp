class RandomizedSet {
    unordered_map<int, int> pos;
    vector<int> arr;
public:
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if (pos.count(val)) return false;
        arr.push_back(val);
        pos[val] = arr.size() - 1;
        return true;
    }
    
    bool remove(int val_x) {
        if (pos.count(val_x) == 0) return false;
        int idx_x = pos[val_x];
        int idx_y = arr.size() - 1;
        int val_y = arr[idx_y];

        swap(arr[idx_x], arr[idx_y]);
        pos[val_y] = idx_x;
        arr.pop_back();
        pos.erase(val_x);

        return true;
    }
    
    int getRandom() {
        int idx = rand() % arr.size();
        return arr[idx];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */