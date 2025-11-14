#define debug(x) cout << #x << " is " << x << endl;

class TwoSum {
    typedef long long ll;
    unordered_map<ll, ll> um;
public:
    TwoSum() {
    }
    
    void add(int number) {
        um[number]++;
    }
    
    bool find(int value) {
        for (auto [num, cnt]: um) {
            ll complement = value - num;
            if (complement == num && um.count(num) && um[num] >= 2)     
                return true;
            if (complement != num && um.count(complement)) 
                return true; 
            
        }
        return false;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */