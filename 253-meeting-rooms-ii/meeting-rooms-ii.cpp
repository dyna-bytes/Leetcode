#ifdef DBG
#define debug(x) cout << #x << " is " << x << endl;
#else
#define debug(x)
#endif
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>&b){
            if (a[1] == b[1]) return a[0] < b[0];
            return a[1] < b[1];
        });

        multimap<int, int> mmp = { {0, 0} }; // {E, S}
        for (auto& interval: intervals) {
            int S = interval[0];
            int E = interval[1];

            auto it = mmp.lower_bound(E);
            if (it == mmp.begin()) {
                mmp.insert({E, S});
                debug("FIRST");
                debug(E);
                debug(S);
            } else {
                --it;
                debug("SECOND");
                debug(it->first);
                debug(it->second);
                debug(E);
                debug(S);
                while (it != mmp.begin() && it->first > S) --it;
                if (it->first <= S) {
                    mmp.erase(it);
                    mmp.insert({E, S});
                } else
                    mmp.insert({E, S});
            }
            debug(mmp.size());
        }
        return mmp.size();
    }
};