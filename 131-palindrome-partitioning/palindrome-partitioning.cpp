#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)

class Solution {
    vector<vector<int>> dp;
    bool isPalindrome(string& str, int s, int e) {
        if (s >= e) return false;
        int& ret = dp[s][e];
        if (ret != -1) return ret;

        for (int l = s, r = e - 1; l <= r; l++, r--)
            if (str[l] != str[r]){ 
                return ret = 0;
            }

        return ret = true;
    }

    void f(string& str, int s, vector<string>& chosen, vector<vector<string>>& ret) {
        if (s >= str.size()) {
            ret.push_back(chosen);
            return;
        }
        
        for (int i = s + 1; i <= str.size(); i++) {
            if (isPalindrome(str, s, i)) {
                string substr = str.substr(s, i - s);
                chosen.push_back(substr);
                f(str, i, chosen, ret);
                chosen.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string str) {
        vector<vector<string>> ret;
        vector<string> chosen;
        int N = str.size();
        dp.resize(N + 1, vector<int>(N + 1, -1));
        f(str, 0, chosen, ret);
        return ret;
    }
};