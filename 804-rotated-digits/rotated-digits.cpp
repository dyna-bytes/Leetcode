class Solution {
    set<int> themselves = {'0', '1', '8'};
    set<int> eachothers = {'2', '5', '6', '9'};
    set<int> invalids = {'3', '4', '7'};
public:
    int rotatedDigits(int n) {
        auto is_valid = [&](string& s) {
            bool valid = false;
            for (char c: s) {
                if (invalids.count(c)) 
                    return false;
                if (eachothers.count(c))
                    valid = true;
            }
            return valid;
        };

        int ret = 0;
        for (int i = 1; i <= n; i++) {
            string s = to_string(i);

            if (is_valid(s))
                ret++;    
        }
        return ret;
    }
};