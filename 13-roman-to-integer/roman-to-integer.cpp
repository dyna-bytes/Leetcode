class Solution {
    map<char, int> um;
public:
    Solution () {
        um['I'] = 1;
        um['V'] = 5;
        um['X'] = 10;
        um['L'] = 50;
        um['C'] = 100;
        um['D'] = 500;
        um['M'] = 1000;
    }

    int romanToInt(string s) {
        int num = 0;
        for (int i = 0; i < s.size(); i++) {
            if (i + 1 < s.size() && um[s[i]] < um[s[i+1]]) {
                num += (um[s[i+1]] - um[s[i]]);
                i++;
            } else {
                num += um[s[i]];
            }
        }

        return num;
    }
};