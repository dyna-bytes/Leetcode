class Solution {
    typedef long long ll;
public:
    long long sumAndMultiply(int n) {
        string s = to_string(n);
        string concat;
        for (int i = 0; i < s.size(); i++)
            if (s[i] != '0') concat.push_back(s[i]);

        ll x = concat.size() == 0 ? 0 : stoll(concat);
        ll sum = 0;
        for (char c: concat) sum += (c - '0');
        return x * sum;
    }
};