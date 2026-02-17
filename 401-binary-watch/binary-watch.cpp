#define debug(x) cout << #x << " is " << x << endl

class Solution {
    typedef long long ll;
    map<ll, int> mp;
    vector<string> ret;

    string min_to_time(int mins) {
        int h = mins / 60;
        int m = mins % 60;
        return to_string(h) + ":" + (m < 10 ? "0" : "") + to_string(m);
    }

    void dfs(int idx, int turnedOn, ll bits) {
        if (turnedOn == 0) {
            int res = 0;
            for (int b = 0; b < 6; ++b) {
                if ((1 << b) & bits)
                    res += mp[1 << b];
            }

            if (res >= 60) return;

            for (int b = 6; b < 10; ++b) {
                if ((1 << b) & bits)
                    res += mp[1 << b];
            }
            
            if (res >= 720) return;
            
            ret.push_back(min_to_time(res));
            return;
        } else if (idx >= 10)
            return;

        dfs(idx + 1, turnedOn - 1, bits + (1LL << idx));
        dfs(idx + 1, turnedOn, bits);
    }
public:
    vector<string> readBinaryWatch(int turnedOn) {
        mp[1 << 0] = 1;
        mp[1 << 1] = 2;
        mp[1 << 2] = 4;
        mp[1 << 3] = 8;
        mp[1 << 4] = 16;
        mp[1 << 5] = 32;
        mp[1 << 6] = 60;
        mp[1 << 7] = 120;
        mp[1 << 8] = 240;
        mp[1 << 9] = 480;

        dfs(0, turnedOn, 0LL);
        return ret;
    }
};