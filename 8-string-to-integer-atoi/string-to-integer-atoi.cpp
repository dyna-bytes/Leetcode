class Solution {
    typedef long long ll;
    
    string get_whitespace_out(string& s) {
        int i;
        for (i = 0; i < s.size(); i++) {
            if (s[i] != ' ') break;
        }
        return s.substr(i);
    }
    string check_sign(string& s, bool& sign) {
        if (s[0] == '-') {
            sign = false;
            return s.substr(1);
        } else if (s[0] == '+') {
            sign = true;
            return s.substr(1);
        }
        
        sign = true;
        return s;
    }
    ll convert(string& s) {
        int i;
        for (i = 0; i < s.size(); i++) 
            if (s[i] != '0') break;
        
        s = s.substr(i);
        ll ret = 0;
        for (i = 0; i < s.size(); i++) {
            if (s[i] < '0' || s[i] > '9') break;
            if (ret < INT_MIN || ret > INT_MAX) return ret;
            ret *= 10;
            ret += (s[i] - '0');
        }
        return ret;
    }
public:
    int myAtoi(string s) {
        s = get_whitespace_out(s);
        bool pos;
        s = check_sign(s, pos);
        ll ret = convert(s) * (pos ? 1 : -1);

        return max((ll)INT_MIN, min((ll)INT_MAX, ret));
    }
};