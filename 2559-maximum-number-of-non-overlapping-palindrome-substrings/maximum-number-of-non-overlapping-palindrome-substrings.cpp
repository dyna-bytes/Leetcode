#define debug(x) cout << __func__ << " " << #x << " is " << x << endl;
class Solution {
    typedef pair<int, int> pii;
    string str;
    vector<vector<int>> dp;
    bool isPal(int l, int r) {
        if (l >= r) return true;
        int& ret = dp[l][r];
        if (ret != -1) return ret;
        
        if (str[l] == str[r])
            return ret = isPal(l + 1, r - 1);
        return ret = false;
    }
public:
    int maxPalindromes(string s, int k) {
        this->str = s;
        vector<pii> pals;
        int n = s.size();
        dp.resize(n + 1, vector<int>(n + 1, -1));
        
        for (int i = 0; i < str.size(); i++) {
            for (int j = i + k; j <= str.size(); j++) {
                if (isPal(i, j - 1))
                    pals.push_back({ i, j });
            }
        }

        if (pals.empty()) return 0;
        
        sort(pals.begin(), pals.end(), [](const pii& l, const pii& r) {
            auto [ls, le] = l;
            auto [rs, re] = r;
            if (le == re) return ls < rs;
            return le < re;
        });

        int ret = !(pals.empty());
        int pe = pals[0].second;
        for (auto& [s, e]: pals) {
            if (pe <= s) {
                ret++;
                pe = e;
            }
        }
        return ret;
    }
};