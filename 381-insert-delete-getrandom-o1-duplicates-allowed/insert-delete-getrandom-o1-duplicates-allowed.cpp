#define debug(x) cout << #x << " is " << x << endl;
class RandomizedCollection {
    map<int, vector<int>> um;
    vector<int> v;
public:
    RandomizedCollection() {
    }
    
    bool insert(int x) {
        bool ret = !um.count(x);
        v.push_back(x);
        um[x].push_back(v.size() - 1);
        return ret;
    }
    
    bool remove(int x) {
        if (!um.count(x)) return false;

        int idx_x = um[x].back();
        int idx_y = v.size() - 1;
        int y = v[idx_y];

        v[idx_x] = y;
        for (auto& _idx_y: um[y]) {
            if (_idx_y == idx_y) {
                _idx_y = idx_x;
                break;
            }
        }

        v.pop_back();
        um[x].pop_back();
        if (um.at(x).size() == 0)
            um.erase(x);

        return true;
    }
    
    int getRandom() {
        return v[random() % v.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */