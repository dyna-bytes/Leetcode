#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    typedef pair<int, int> pii;
public:
    vector<int> amountPainted(vector<vector<int>>& paint) {
        int n = paint.size();
        vector<int> worklog(n);
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int s = paint[i][0], e = paint[i][1];
            auto it = mp.upper_bound(s);
            if (it != mp.begin()) --it;

            int min_s = s;
            int max_e = e;
            int len = 0;
            while (it != mp.end() && it->first < e) {
                if (it->second <= s) {
                    ++it;
                    continue;
                } else if (it->first < e) {
                    len += (it->second - it->first);
                }

                min_s = min(min_s, it->first);
                max_e = max(max_e, it->second);
                it = mp.erase(it);
            }

            mp.insert({ min_s, max_e });
            worklog[i] = max_e - min_s - len;
        }
        return worklog;
    }
};