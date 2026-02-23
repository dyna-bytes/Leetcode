class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        unordered_set<string> us;
        for (int i = 0; i + k <= n; ++i) {
            us.insert(s.substr(i, k));
        }

        return us.size() == pow(2, k);
    }
};