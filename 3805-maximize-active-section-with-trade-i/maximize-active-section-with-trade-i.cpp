class Solution {
public:
    int maxActiveSectionsAfterTrade(string str) {
        int num_ones = count(str.begin(), str.end(), '1');
        str = '1' + str;
        str.push_back('1');

        vector<string> segs;
        int s, e;
        for (s = 0, e = 0; e < str.size(); e++) {
            if (str[e] != str[s]) {
                segs.push_back(str.substr(s, e - s));
                s = e;
            }
        }
        segs.push_back(str.substr(s, e - s));

        unsigned long max_delta = 0;
        for (int i = 1; i < segs.size() - 1; ++i) {
            if (segs[i][0] == '1') {
                max_delta = max(max_delta, segs[i-1].size() + segs[i+1].size());
            }
        }

        return max_delta + num_ones;
    }
};