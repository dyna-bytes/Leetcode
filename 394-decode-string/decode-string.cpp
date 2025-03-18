class Solution {
public:
    string decodeString(string s) {
        auto strmul = [](int k, string& str) {
            string ret;
            while (k--)
                ret += str;
            return ret;
        };

        stack<char> S;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ']') {
                string Q;
                while (S.top() != '[') {
                    Q += S.top();
                    S.pop();
                }
                S.pop();

                string N;
                while (!S.empty() && S.top() >= '0' && S.top() <= '9') {
                    N += S.top();
                    S.pop();
                }
                
                reverse(N.begin(), N.end());
                int k = stoi(N);
                
                Q = strmul(k, Q);
                for (int j = Q.size()-1; j >= 0; j--)
                    S.push(Q[j]);
            } else 
                S.push(s[i]);
        }

        string ret;
        while (!S.empty()) {
            ret += S.top(); S.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};