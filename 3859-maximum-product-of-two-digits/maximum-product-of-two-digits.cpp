class Solution {
public:
    int maxProduct(int n) {
        string s = to_string(n);
        sort(s.begin(), s.end(), greater<char>());
        return (s[0] - '0') * (s[1] - '0');
    }
};