class Solution {
public:
    int minOperations(string s) {
        int ans;
        char minc = *min_element(s.begin(), s.end());

        if (minc != 'a') {
            ans = ('a' - minc + 26) % 26;
            return ans;
        }

        char maxc = *max_element(s.begin(), s.end());
        if (maxc == 'a')
            return 0;

        minc = 'z';
        for (char& c: s) {
            if (c == 'a') continue;
            minc = min(minc, c);
        }

        ans = ('a' - minc + 26) % 26;
        return ans;
    }
};