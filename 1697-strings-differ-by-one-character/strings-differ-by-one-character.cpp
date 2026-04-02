class Solution {
    typedef  unsigned long long ull;
    ull x = 27;

    typedef pair<ull, ull> pull;
    vector<ull> pow_x;


    ull hash(char c, int idx) {
        ull ret = c;
        ret *= pow_x[idx];
        
        return ret;
    }
    ull hash(const string& s) {
        ull ret = 0;
        for (int i = 0; i < s.size(); i++) {
            ret += hash(s[i], i);
        }
        return ret;
    }
public:
    bool differByOne(vector<string>& dict) {
        int n = dict.size();
        if (n == 0) return false;

        vector<ull> hashes(n);
        pow_x.resize(dict[0].size() + 1);
        pow_x[0] = 1;
        for (int i = 1; i < dict[0].size(); i++)
            pow_x[i] = pow_x[i - 1] * x;

        for (int i = 0; i < n; i++) {
            hashes[i] = hash(dict[i]);
        }

        for (int k = 0; k < dict[0].size(); k++) {
            unordered_map<ull, ull> um;
            for (int i = 0; i < n; i++) {
                ull target = (hashes[i] - hash(dict[i][k], k));
                if (um[target]++ > 0) return true;
            }
        }
        return false;
    }
};