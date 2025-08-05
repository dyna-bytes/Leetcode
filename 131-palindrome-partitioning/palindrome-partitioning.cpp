#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)

class Solution {
    #define FOUND 2
    #define EMPTY 1
    unordered_map<string, int> dp;
    bool isPalindrome(string& str) {
        if (str.size() == 0) return false;
        int& ret = dp[str];
        if (ret) return (ret == FOUND);

        for (int l = 0, r = str.size() - 1; l <= r; l++, r--)
            if (str[l] != str[r]){ 
                ret = EMPTY;
                return false;
            }

        ret = FOUND;
        return true;
    }

    void f(string& str, int s, vector<string>& chosen, vector<vector<string>>& ret) {
        if (s >= str.size()) {
            ret.push_back(chosen);
            return;
        }
        
        for (int i = s + 1; i <= str.size(); i++) {
            string substr = str.substr(s, i - s);
            if (isPalindrome(substr)) {
                chosen.push_back(substr);
                f(str, i, chosen, ret);
                chosen.pop_back();
            }
        }
    }
public:
    bool check(string& str, int s, int e) {
        if (s >= e) return false;
        for (int l = s, r = e - 1; l <= r; l++, r--)
            if (str[l] != str[r]) return false;
        return true;
    }
    vector<vector<string>> partition(string str) {
        vector<vector<string>> ret;
        vector<string> chosen;
        f(str, 0, chosen, ret);
        return ret;
    }
};